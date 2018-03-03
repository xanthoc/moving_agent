#pragma once
#include "MyConfig.h"
#include "MyClock.h"
#include "Vehicle.h"

class GameWorld
{
	Vehicle *m_vehicle;
	int m_width;
	int m_height;
public:
	GameWorld();
	~GameWorld();
	int width() const { return m_width; }
	int height() const { return m_height; }
	void set_width(int val) { m_width = val; }
	void set_height(int val) { m_height = val; }
	void update(double time_elapsed);
	void render(HDC hdc);

};

