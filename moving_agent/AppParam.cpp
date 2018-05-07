#include "stdafx.h"
#include "AppParam.h"
#include "IniFileLoader.h"


AppParam::AppParam()
{
	//IniFileLoader loader("C:\\Users\\xanthoc\\Documents\\Visual Studio 2015\\Projects\\moving_agent\\params.ini");
	IniFileLoader loader("params.ini");
	m_num_obstacles = loader.get_parameter_as_int();
	m_min_obstacle_radius = loader.get_parameter_as_double();
	m_max_obstacle_radius = loader.get_parameter_as_double();
	m_min_dist_btn_obstacle = loader.get_parameter_as_double();
	m_steering_force_tweaker = loader.get_parameter_as_double();
	m_steering_force = loader.get_parameter_as_double();
	m_max_speed = loader.get_parameter_as_double();
	m_vehicle_mass = loader.get_parameter_as_double();
	m_vehicle_scale = loader.get_parameter_as_double();
	m_view_distance = loader.get_parameter_as_double();
	m_min_detection_box_length = loader.get_parameter_as_double();
}


AppParam::~AppParam()
{
}


AppParam& AppParam::instance() {
	static AppParam ins;
	return ins;
}
