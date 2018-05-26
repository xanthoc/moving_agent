#pragma once
#include "MyConfig.h"
#include "MyClock.h"
#include "Vehicle.h"
#include "Obstacle.h"
#include "Wall.h"
#include <vector>

class GameWorld
{
	int m_width;
	int m_height;
	double m_panic_dist;
	Vector2D m_target;
	HBITMAP m_crosshair, m_old_crosshair;
	HDC m_hdcmem;

	std::vector<Obstacle*> m_obstacles;
	std::vector<Wall*> m_walls;
	std::vector<Vehicle*> m_agents;

	void create_wall();
	void create_obstacle();
	void create_agent();

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
	void render();
	void create_detail() {
		// create_detail is called when WM_SIZE is received, so check whether each container is empty
		//if (m_walls.empty()) create_wall();
		if (m_obstacles.empty()) create_obstacle();
		if (m_agents.empty()) create_agent();
	}
	std::vector<Obstacle*> &obstacles() { return m_obstacles; }
	std::vector<Wall*> &walls() { return m_walls; }
	std::vector<Vehicle*> &agents() { return m_agents; }

	Vehicle* wolf() { return m_agents[0]; }
	Vehicle* sheep(int order = 1) { return m_agents[order]; }

};

