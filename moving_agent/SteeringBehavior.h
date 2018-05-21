#pragma once
#include "Vector2D.h"
#include <vector>
#include "Obstacle.h"
#include "Wall.h"

class Vehicle;

class SteeringBehavior
{
	Vehicle *m_vehicle;
	bool m_seek_flag;
	bool m_flee_flag;

	bool m_arrive_flag;
	enum Deceleration { SLOW = 3, NORMAL = 2, FAST = 1 };

	bool m_pursuit_flag;

	bool m_wander_flag;
	double m_wander_radius;
	double m_wander_dist;
	double m_wander_jitter;
	Vector2D m_wander_target;

	bool m_obstacle_avoidance_flag;

	bool m_wall_avoidance_flag;

public:
	SteeringBehavior(Vehicle *vehicle);
	~SteeringBehavior();
	Vector2D calculate();
	bool accumulate_force(Vector2D &running_total, const Vector2D &force_to_add);
	Vector2D seek(const Vector2D &target_pos);
	Vector2D flee(const Vector2D &target_pos);
	Vector2D arrive(const Vector2D &target_pos, const Deceleration decel);
	Vector2D pursuit(Vehicle *evader);
	Vector2D wander();
	Vector2D obstacle_avoidance(const std::vector<Obstacle*> &obstacles);
	Vector2D wall_avoidance(const std::vector<Wall*> &walls);
	void render_wander_status();
	void render_detection_box();
	void render_feeler();
	void set_seek(bool val) { m_seek_flag = val; }
	void set_flee(bool val) { m_flee_flag = val; }
	void set_arrive(bool val) { m_arrive_flag = val; }
	void set_pursuit(bool val) { m_pursuit_flag = val; }
	void set_wander(bool val) { m_wander_flag = val; }
	void set_obstacle_avoidance(bool val) { m_obstacle_avoidance_flag = val; }
	void set_wall_avoidance(bool val) { m_wall_avoidance_flag = val; }
};

