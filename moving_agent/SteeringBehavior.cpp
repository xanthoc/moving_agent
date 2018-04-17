#include "stdafx.h"
#include "SteeringBehavior.h"
#include "Vehicle.h"
#include "GameWorld.h"


SteeringBehavior::SteeringBehavior(Vehicle *vehicle) : m_vehicle(vehicle), 
m_seek_flag(false), m_flee_flag(false), m_arrive_flag(false)
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
	if (m_seek_flag) {
		Vector2D tmp = seek(m_vehicle->world()->target());
		if (!accumulate_force(force, tmp)) return force;
	}
	if (m_arrive_flag) {
		Vector2D tmp = arrive(m_vehicle->world()->target(), SLOW);
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
	if (distance.length_sq() > 100.0*100.0) {
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