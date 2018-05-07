#pragma once
#include "BaseGameEntity.h"

class Obstacle : public BaseGameEntity
{
public:
	Obstacle(const Vector2D pos, double br) : BaseGameEntity(pos, br) {}
	~Obstacle() {}
	void update(double elapsed_time) {}
	void render();
};

