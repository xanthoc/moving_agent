#include "stdafx.h"
#include "MovingEntity.h"


MovingEntity::MovingEntity() : m_mass(1.0), m_max_force(100.0), m_max_speed(100.0), m_max_turn_rate(3.14159)
{
	m_velocity = Vector2D(1.0, 0.0);
	m_side = Vector2D(0.0, 1.0);
}


MovingEntity::~MovingEntity()
{
}
