#pragma once
#include "Vector2D.h"

class Vehicle;

class SteeringBehavior
{
	Vehicle *m_vehicle;
	bool m_seek_flag;
	bool m_flee_flag;
	bool m_arrive_flag;
	enum Deceleration { SLOW=3, NORMAL=2, FAST=1 };
public:
	SteeringBehavior(Vehicle *vehicle);
	~SteeringBehavior();
	Vector2D calculate();
	bool accumulate_force(Vector2D &running_total, const Vector2D &force_to_add);
	Vector2D seek(const Vector2D &target_pos);
	Vector2D flee(const Vector2D &target_pos);
	Vector2D arrive(const Vector2D &target_pos, const Deceleration decel);
	void set_seek(bool val) { m_seek_flag = val; }
	void set_flee(bool val) { m_flee_flag = val; }
	void set_arrive(bool val) { m_arrive_flag = val; }
};

