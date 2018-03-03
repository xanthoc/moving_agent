#pragma once
#include "BaseGameEntity.h"

class MovingEntity : public BaseGameEntity
{
protected:
	Vector2D m_velocity;
	Vector2D m_heading; // normalized velocity
	Vector2D m_side; // perpendicular to heading
	double m_mass;
	double m_max_speed;
	double m_max_force; // the max force that this entity can produce (think rockets and thrust)
	double m_max_turn_rate;

public:
	MovingEntity();
	virtual ~MovingEntity();
};

