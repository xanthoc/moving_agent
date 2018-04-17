#pragma once
#include "Vector2D.h"

class Vehicle;

class SteeringBehavior
{
	Vehicle *m_vehicle;
	bool m_seek_flag;
	bool m_flee_flag;
public:
	SteeringBehavior(Vehicle *vehicle);
	~SteeringBehavior();
	Vector2D calculate();
	bool accumulate_force(Vector2D &running_total, const Vector2D &force_to_add);
	Vector2D seek(const Vector2D &target_pos);
	Vector2D flee(const Vector2D &target_pos);
	void set_seek(bool val) { m_seek_flag = val; }
	void set_flee(bool val) { m_flee_flag = val; }
};

