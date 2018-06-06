#pragma once
#include "MyConfig.h"
#include "MyClock.h"
#include "Vehicle.h"
#include "Obstacle.h"
#include "Wall.h"
#include "Cell.h"
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

	std::vector<Cell> m_cells;
	int m_num_xcells;
	int m_num_ycells;

	void create_wall();
	void create_obstacle();
	void create_agent();

	int get_cell_id(const Vector2D &pos);

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
		double width = ((double)m_width) / m_num_xcells;
		double height = ((double)m_height) / m_num_ycells;
		for (int i = 0; i < m_num_ycells; ++i) {
			for (int j = 0; j < m_num_xcells; ++j) {
				Vector2D top_left = Vector2D(j*width, i*height);
				Vector2D bottom_right = Vector2D((j+1)*width, (i+1)*height);
				m_cells.push_back(Cell(top_left, bottom_right));
			}
		}
		//if (m_walls.empty()) create_wall();
		if (m_obstacles.empty()) create_obstacle();
		if (m_agents.empty()) create_agent();
	}
	std::vector<Obstacle*> &obstacles() { return m_obstacles; }
	std::vector<Wall*> &walls() { return m_walls; }
	std::vector<Vehicle*> &agents() { return m_agents; }
	std::vector<Cell> &cells() { return m_cells; }

	Vehicle* wolf() { return m_agents[0]; }
	Vehicle* sheep(int order = 1) { return m_agents[order]; }

};

