#pragma once
class AppParam
{
	int m_num_agents;
	int m_num_obstacles;
	double m_min_obstacle_radius;
	double m_max_obstacle_radius;
	double m_min_dist_btn_obstacle;
	//this is used to multiply the steering force AND all the multipliers
	//found in SteeringBehavior
	double m_steering_force_tweaker;

	double m_steering_force;
	double m_max_speed;
	double m_vehicle_mass;
	double m_vehicle_scale;
	//how close a neighbour must be before an agent perceives it (considers it
	//to be within its neighborhood)
	double m_view_distance;

	//used in obstacle avoidance
	double m_min_detection_box_length;

	AppParam();
	~AppParam();

public:
	int num_agents() const { return m_num_agents; }
	int num_obstacles() const { return m_num_obstacles; }
	double min_obstacle_radius() const { return m_min_obstacle_radius; }
	double max_obstacle_radius() const { return m_max_obstacle_radius; }
	double min_dist_btn_obstacle() const { return m_min_dist_btn_obstacle; }
	double steering_force_tweaker() const { return m_steering_force_tweaker; }
	double steering_force() const { return m_steering_force; }
	double max_speed() const { return m_max_speed; }
	double vehicle_mass() const { return m_vehicle_mass; }
	double vehicle_scale() const { return m_vehicle_scale; }
	double view_distance() const { return m_view_distance; }
	double min_detection_box_length() const { return m_min_detection_box_length; }

	static AppParam &instance();

};

#define app_param AppParam::instance()

