#include "stdafx.h"
#include "MovingEntity.h"
#include "AppParam.h"

MovingEntity::MovingEntity() : m_mass(app_param.vehicle_mass()), 
m_max_force(app_param.steering_force()*app_param.steering_force_tweaker()), 
m_max_speed(app_param.max_speed()), m_max_turn_rate(3.14159)
{
	m_velocity = Vector2D(1.0, 0.0);
	m_side = Vector2D(0.0, 1.0);
}


MovingEntity::MovingEntity(const Vector2D &pos, double br) : m_mass(app_param.vehicle_mass()),
m_max_force(app_param.steering_force()*app_param.steering_force_tweaker()),
m_max_speed(app_param.max_speed()), m_max_turn_rate(3.14159), BaseGameEntity(pos, br)
{
	m_velocity = Vector2D(1.0, 0.0);
	m_side = Vector2D(0.0, 1.0);
}


MovingEntity::~MovingEntity()
{
}
