#pragma once
#include "Vector2D.h"

class Vehicle;

class SteeringBehavior
{
	Vehicle *m_vehicle;
public:
	SteeringBehavior(Vehicle *vehicle);
	~SteeringBehavior();
	Vector2D calculate();
	bool accumulate_force(Vector2D &running_total, const Vector2D &force_to_add);
	Vector2D seek(const Vector2D &target_pos);
};

