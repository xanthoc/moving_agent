#pragma once
#include "MyConfig.h"
#include "MyClock.h"
#include "Vehicle.h"
#include "Obstacle.h"
#include <vector>

class GameWorld
{
	Vehicle *m_sheep;
	Vehicle *m_wolf;
	int m_width;
	int m_height;
	double m_panic_dist;
	Vector2D m_target;
	HBITMAP m_crosshair, m_old_crosshair;
	HDC m_hdcmem;

	std::vector<Obstacle*> m_Obstacles;

public:
	GameWorld();
	~GameWorld();
	int width() const { return m_width; }
	int height() const { return m_height; }
	double panic_dist() const { return m_panic_dist; }
	void set_width(int val) { m_width = val; }
	void set_height(int val) { m_height = val; }
	void set_panic_dist(double val) { m_panic_dist = val; }
	Vector2D target() { return m_target; }
	void set_target(int x, int y) { m_target = Vector2D(x, y); }
	void update(double time_elapsed);
	void render(HDC hdc);

	Vehicle* sheep() { return m_sheep; }
	Vehicle* wolf() { return m_wolf; }

};

