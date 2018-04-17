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
	void render(HDC hdc);
	void set_seek(bool val) { m_steering->set_seek(val); }
	void set_flee(bool val) { m_steering->set_flee(val); }
};

