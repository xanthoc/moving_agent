#include "stdafx.h"
#include "SteeringBehavior.h"
#include "Vehicle.h"
#include "GameWorld.h"
#include "MyRand.h"
#include "MyGDI.h"
#include "AppParam.h"
#include "EntityFunctionTemplates.h"
#include "Geometry.h"

SteeringBehavior::SteeringBehavior(Vehicle *vehicle) : m_vehicle(vehicle), 
m_seek_flag(false), m_flee_flag(false), m_arrive_flag(false), m_pursuit_flag(false), m_wander_flag(false),
m_wander_radius(20.0), m_wander_dist(50.0), m_wander_jitter(30.0), m_wander_target(Vector2D(m_wander_radius, 0.0))
{
}


SteeringBehavior::~SteeringBehavior()
{
}


Vector2D SteeringBehavior::calculate() {
	Vector2D force;
	if (m_wall_avoidance_flag) {
		Vector2D tmp = wall_avoidance(m_vehicle->world()->walls());
		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_obstacle_avoidance_flag) {
		Vector2D tmp = obstacle_avoidance(m_vehicle->world()->obstacles());
		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_flee_flag) {
//		Vector2D tmp = flee(m_vehicle->world()->wolf()->pos());
//		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_pursuit_flag) {
//		Vector2D tmp = pursuit(m_vehicle->world()->sheep());
//		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_seek_flag) {
		Vector2D tmp = seek(m_vehicle->world()->target());
		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_arrive_flag) {
		Vector2D tmp = arrive(m_vehicle->world()->target(), SLOW);
		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_wander_flag) {
		Vector2D tmp = wander();
		if (!accumulate_force(force, tmp)) return force;
	}
	return force;
}

bool SteeringBehavior::accumulate_force(Vector2D &running_total, const Vector2D &force_to_add) {
	double mag_so_far = running_total.length();
	double mag_remaining = m_vehicle->max_force() - mag_so_far;
	if (mag_remaining < 0.0) return false;
	double mag_to_add = force_to_add.length();
	if (mag_to_add < mag_remaining) {
		running_total += force_to_add;
	}
	else {
		running_total += force_to_add.get_normalized()*mag_remaining;
	}
	return true;
}

Vector2D SteeringBehavior::seek(const Vector2D &target_pos) {
	Vector2D res = target_pos - m_vehicle->pos();
	res = res.get_normalized();
	res = res * m_vehicle->max_speed();
	return res - m_vehicle->velocity();
}

Vector2D SteeringBehavior::flee(const Vector2D &target_pos) {
	Vector2D distance = m_vehicle->pos() - target_pos;
	if (distance.length_sq() > m_vehicle->world()->panic_dist()*m_vehicle->world()->panic_dist()) {
		return Vector2D(0.0, 0.0);
	}
	distance = distance.get_normalized();
	distance = distance * m_vehicle->max_speed();
	return distance - m_vehicle->velocity();
}

Vector2D SteeringBehavior::arrive(const Vector2D &target_pos, const Deceleration decel) {
	Vector2D res = target_pos - m_vehicle->pos();
	double dist = res.length();
	if (dist > 0) {
		double decel_tweaker = 0.3;
		double speed = dist / (decel_tweaker*decel);
		speed = min(speed, m_vehicle->max_speed());
		res *= speed / dist;
		return res - m_vehicle->velocity();
	}
	return Vector2D(0.0, 0.0);
}

Vector2D SteeringBehavior::pursuit(Vehicle *evader) {
	Vector2D to_evader = evader->pos() - m_vehicle->pos();
	double look_ahead_time = to_evader.length() / (m_vehicle->max_speed() + evader->velocity().length());
	return seek(evader->pos() + evader->velocity()*look_ahead_time);
}

Vector2D SteeringBehavior::wander() {
	m_wander_target += Vector2D(m_wander_jitter*(my_rand.drand()-0.5)*2.0, m_wander_jitter*(my_rand.drand()-0.5)*2.0);
	m_wander_target = m_wander_target.get_normalized();
	m_wander_target *= m_wander_radius;
	//m_wander_target = Vector2D(0.0, -m_wander_radius);
	Vector2D tmp = m_wander_target + Vector2D(m_wander_dist, 0);
	Vector2D target_pos = to_world_space(tmp, m_vehicle->heading(), m_vehicle->side(), m_vehicle->pos());
	Vector2D to_target = target_pos - m_vehicle->pos();
	return to_target;// -m_vehicle->velocity();
}

void SteeringBehavior::render_wander_status() {
	if (!m_wander_flag) return;
	Vector2D circle_origin = Vector2D(m_wander_dist, 0);
	Vector2D circle_origin_world = to_world_space(circle_origin, m_vehicle->heading(), m_vehicle->side(), m_vehicle->pos());
	my_gdi.draw_empty_circle(circle_origin_world, m_wander_radius);
	Vector2D tmp = m_wander_target + Vector2D(m_wander_dist, 0);
	Vector2D target_pos = to_world_space(tmp, m_vehicle->heading(), m_vehicle->side(), m_vehicle->pos());
	int small_radius = 4;
	my_gdi.draw_empty_circle(target_pos, small_radius);
}

Vector2D SteeringBehavior::obstacle_avoidance(const std::vector<Obstacle*> &obstacles) {
	Vector2D res;
	double detection_box_len = app_param.min_detection_box_length()*(1.0 + m_vehicle->velocity().length() / m_vehicle->max_speed());
	tag_neighbor(m_vehicle, obstacles, detection_box_len);
	double inter_max = 10000000.0;
	Obstacle* inter_ob = nullptr;
	Vector2D inter_local;
	for (std::vector<Obstacle*>::const_iterator iter = obstacles.begin(); iter != obstacles.end(); ++iter) {
		if ((*iter)->is_tagged()) {
			Vector2D pos_local = to_local_space((*iter)->pos(), m_vehicle->heading(), m_vehicle->side(), m_vehicle->pos());
			//Vector2D pos_world = to_world_space(pos_local, m_vehicle->heading(), m_vehicle->side(), m_vehicle->pos());
			double expanded_radius = (*iter)->bounding_radius() + m_vehicle->bounding_radius();
			if (pos_local.m_x > 0.0 && fabs(pos_local.m_y) < expanded_radius) {
				(*iter)->set_scale(Vector2D(2.0, 2.0));
				double sqrt_part = sqrt(expanded_radius*expanded_radius - pos_local.m_y*pos_local.m_y);
				double inter_dist = pos_local.m_x - sqrt_part;
				if (inter_dist < 0.0) inter_dist = pos_local.m_x + sqrt_part;
				if (inter_dist < inter_max) {
					inter_max = inter_dist;
					inter_ob = *iter;
					inter_local = pos_local;
				}
			}
		}
	}
	if (inter_ob) {
		inter_ob->set_scale(Vector2D(3.0, 3.0));
		double weight = 1.0 + (detection_box_len - inter_local.m_x) / detection_box_len;
		double fy = inter_ob->bounding_radius() + m_vehicle->bounding_radius() - fabs(inter_local.m_y);
		fy = inter_local.m_y > 0 ? -fy : fy;
		fy *= 15.0*weight;
		double fx = -0.5*(detection_box_len + inter_ob->bounding_radius() - inter_local.m_x);
		res = Vector2D(fx, fy);
		res = to_world_space(res, m_vehicle->heading(), m_vehicle->side(), Vector2D(0.0, 0.0));
	}
	return res;
}

void SteeringBehavior::render_detection_box() {
	if (!m_obstacle_avoidance_flag) return;
	double detection_box_len = app_param.min_detection_box_length()*(1.0 + m_vehicle->velocity().length() / m_vehicle->max_speed());
	std::vector<Vector2D> pts;
	pts.push_back(Vector2D(0, m_vehicle->bounding_radius()));
	pts.push_back(Vector2D(0, -m_vehicle->bounding_radius()));
	pts.push_back(Vector2D(detection_box_len, -m_vehicle->bounding_radius()));
	pts.push_back(Vector2D(detection_box_len, m_vehicle->bounding_radius()));
	for (unsigned i = 0; i < pts.size(); ++i) {
		pts[i] = to_world_space(pts[i], m_vehicle->heading(), m_vehicle->side(), m_vehicle->pos());
	}
	my_gdi.draw_closed_shape(pts);
}

Vector2D SteeringBehavior::wall_avoidance(const std::vector<Wall*> &walls) {
	Vector2D force;
	// create three feelers
	std::vector<Vector2D> feelers;
	feelers.push_back(m_vehicle->pos() + m_vehicle->heading()*m_vehicle->scale().length() * 4);
	feelers.push_back(m_vehicle->pos() + (m_vehicle->heading() + m_vehicle->side()).get_normalized()*m_vehicle->scale().length() * 4);
	feelers.push_back(m_vehicle->pos() + (m_vehicle->heading() - m_vehicle->side()).get_normalized()*m_vehicle->scale().length() * 4);
	// find the nearest wall that intersects with any of the feelers
	for (auto itf = feelers.begin(); itf != feelers.end(); ++itf) {
		Wall *pwall = nullptr; // pointer to nearest intersecting wall
		Vector2D ipt; // nearest intersection point
		double dist_to_ipt = std::numeric_limits<double>::infinity(); // distance to the nearest intersecting point
		for (auto iter = (m_vehicle->world()->walls()).begin(); iter != (m_vehicle->world()->walls()).end(); ++iter) {
			if (intersect_two_lines(m_vehicle->pos(), *itf, (*iter)->from(), (*iter)->to())) {
				Vector2D tmp_pt;
				double dist = find_intersecting_point(m_vehicle->pos(), *itf, (*iter)->from(), (*iter)->to(), tmp_pt);
				if (dist < dist_to_ipt) {
					dist_to_ipt = dist;
					ipt = tmp_pt;
					pwall = *iter;
				}
			}
		}
		if (pwall) {
			Vector2D overshoot = *itf - ipt;
			Vector2D steering = pwall->normal();
			steering *= overshoot.length();
			force += steering;
		}
	}
	// if any wall, calculate the force
	return force;
}

void SteeringBehavior::render_feeler() {
	if (!m_wall_avoidance_flag) return;
	std::vector<Vector2D> feelers;
	feelers.push_back(m_vehicle->pos() + m_vehicle->heading()*m_vehicle->scale().length() * 4);
	feelers.push_back(m_vehicle->pos() + (m_vehicle->heading() + m_vehicle->side()).get_normalized()*m_vehicle->scale().length() * 4);
	feelers.push_back(m_vehicle->pos() + (m_vehicle->heading() - m_vehicle->side()).get_normalized()*m_vehicle->scale().length() * 4);
	for (auto iter = feelers.begin(); iter != feelers.end(); ++iter) {
		my_gdi.draw_feeler(m_vehicle->pos(), *iter);
	}
}


