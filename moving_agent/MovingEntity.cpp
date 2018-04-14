#include "stdafx.h"
#include "MovingEntity.h"


MovingEntity::MovingEntity() : m_mass(1.0), m_max_force(100.0), m_max_speed(100.0), m_max_turn_rate(3.14159)
{
}


MovingEntity::~MovingEntity()
{
}
