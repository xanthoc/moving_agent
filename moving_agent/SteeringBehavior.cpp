#include "stdafx.h"
#include "SteeringBehavior.h"
#include "Vehicle.h"
#include "GameWorld.h"


SteeringBehavior::SteeringBehavior(Vehicle *vehicle) : m_vehicle(vehicle) 
{
}


SteeringBehavior::~SteeringBehavior()
{
}


Vector2D SteeringBehavior::calculate() {
	Vector2D force;
	if (true) {
		Vector2D tmp = seek(m_vehicle->world()->target());
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
