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
	Vehicle(GameWorld *world);
	virtual ~Vehicle();
	void update(double time_elapsed);
	void render(HDC hdc);
};

