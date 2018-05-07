#include "stdafx.h"
#include "SteeringBehavior.h"
#include "Vehicle.h"
#include "GameWorld.h"
#include "MyRand.h"
#include "MyGDI.h"


SteeringBehavior::SteeringBehavior(Vehicle *vehicle) : m_vehicle(vehicle), 
m_seek_flag(false), m_flee_flag(false), m_arrive_flag(false), m_pursuit_flag(false), m_wander_flag(false),
m_wander_radius(50.0), m_wander_dist(60.0), m_wander_jitter(40.0), m_wander_target(Vector2D(m_wander_radius, 0.0))
{
}


SteeringBehavior::~SteeringBehavior()
{
}


Vector2D SteeringBehavior::calculate() {
	Vector2D force;
	if (m_flee_flag) {
		Vector2D tmp = flee(m_vehicle->world()->wolf()->pos());
		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_pursuit_flag) {
		Vector2D tmp = pursuit(m_vehicle->world()->sheep());
		if (!accumulate_force(force, tmp)) return force;
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

static Vector2D to_world_space(const Vector2D &target, const Vector2D &heading, const Vector2D &side, const Vector2D &pos) {

	Vector2D res = Vector2D(heading.x()*target.x() + side.x()*target.y(), heading.y()*target.x() + side.y()*target.y());
	res += pos;
	return res;
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