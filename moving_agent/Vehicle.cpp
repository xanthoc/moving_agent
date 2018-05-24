#include "stdafx.h"
#include "Vehicle.h"
#include "GameWorld.h"
#include <vector>
#include "Vector2D.h"
#include "MyGDI.h"

Vehicle::Vehicle(GameWorld *world) : m_world(world), m_steering(new SteeringBehavior(this))
{
	m_scale = Vector2D(10.0, 10.0);
	m_bounding_radius = 6;
}


Vehicle::~Vehicle()
{
	delete m_steering;
}


void Vehicle::update(double time_elapsed) {
	Vector2D steering_force = m_steering->calculate();
	Vector2D acceleration = steering_force / m_mass;
	m_velocity += acceleration * time_elapsed;
	m_velocity.truncate(m_max_speed);
	m_pos += m_velocity * time_elapsed;
	if (m_velocity.length_sq() > 0.00000001) {
		m_heading = m_velocity.get_normalized();
		m_side = m_heading.get_perp();
	}
	m_pos.wrap_around(0, m_world->width(), m_world->height(), 0);
}


void Vehicle::render() {
	//Ellipse(hdc, m_pos.m_x - 5, m_pos.m_y - 5, m_pos.m_x + 5, m_pos.m_y + 5);

	std::vector<Vector2D> pts;
	pts.push_back(Vector2D(-1.0, 0.6));
	pts.push_back(Vector2D(-1.0, -0.6));
	pts.push_back(Vector2D(1.0, 0));

	// scale
	for (unsigned int i = 0; i < pts.size(); ++i) {
		double x = m_scale.m_x*pts[i].m_x;
		double y = m_scale.m_y*pts[i].m_y;
		pts[i] = Vector2D(x, y);
	}

	// rotate
	for (unsigned int i = 0; i < pts.size(); ++i) {
		double x = m_heading.m_x*pts[i].m_x + m_side.m_x*pts[i].m_y;
		double y = m_heading.m_y*pts[i].m_x + m_side.m_y*pts[i].m_y;
		pts[i] = Vector2D(x, y);
	}

	// translate
	for (unsigned int i = 0; i < pts.size(); ++i) {
		pts[i] += m_pos;
	}

	my_gdi.draw_closed_shape(pts);

	m_steering->render_wander_status();
	m_steering->render_detection_box();
	m_steering->render_feeler();
	m_steering->render_steering_force();
}