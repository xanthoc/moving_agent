#include "stdafx.h"
#include "Vehicle.h"
#include "GameWorld.h"
#include <vector>
#include "Vector2D.h"

Vehicle::Vehicle(GameWorld *world) : m_world(world), m_steering(new SteeringBehavior(this))
{
	m_scale = Vector2D(10.0, 10.0);
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


void Vehicle::render(HDC hdc) {
	//Ellipse(hdc, m_pos.x() - 5, m_pos.y() - 5, m_pos.x() + 5, m_pos.y() + 5);

	std::vector<Vector2D> pts;
	pts.push_back(Vector2D(-1.0, 0.6));
	pts.push_back(Vector2D(-1.0, -0.6));
	pts.push_back(Vector2D(1.0, 0));

	// scale
	for (unsigned int i = 0; i < pts.size(); ++i) {
		double x = m_scale.x()*pts[i].x();
		double y = m_scale.y()*pts[i].y();
		pts[i] = Vector2D(x, y);
	}

	// rotate
	for (unsigned int i = 0; i < pts.size(); ++i) {
		double x = m_heading.x()*pts[i].x() + m_side.x()*pts[i].y();
		double y = m_heading.y()*pts[i].x() + m_side.y()*pts[i].y();
		pts[i] = Vector2D(x, y);
	}

	// translate
	for (unsigned int i = 0; i < pts.size(); ++i) {
		pts[i] += m_pos;
	}

	MoveToEx(hdc, (int)pts[0].x(), (int)pts[0].y(), nullptr);
	for (unsigned int p = 1; p<pts.size(); ++p) {
		LineTo(hdc, (int)pts[p].x(), (int)pts[p].y());
	}
	LineTo(hdc, (int)pts[0].x(), (int)pts[0].y());

	m_steering->render_wander_status(hdc);
}