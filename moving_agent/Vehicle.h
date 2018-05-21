#pragma once
#include "MovingEntity.h"
#include "SteeringBehavior.h"

class GameWorld;

class Vehicle : public MovingEntity
{
private:
	GameWorld *m_world;
	SteeringBehavior *m_steering;
public:
	GameWorld* world() { return m_world; }
	Vehicle(GameWorld *world);
	virtual ~Vehicle();
	void update(double time_elapsed);
	void render();
	void set_seek(bool val) { m_steering->set_seek(val); }
	void set_flee(bool val) { m_steering->set_flee(val); }
	void set_arrive(bool val) { m_steering->set_arrive(val); }
	void set_pursuit(bool val) { m_steering->set_pursuit(val); }
	void set_wander(bool val) { m_steering->set_wander(val); }
	void set_obstacle_avoidance(bool val) { m_steering->set_obstacle_avoidance(val); }
	void set_wall_avoidance(bool val) { m_steering->set_wall_avoidance(val); }
};

