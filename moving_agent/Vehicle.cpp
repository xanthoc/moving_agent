#include "stdafx.h"
#include "Vehicle.h"
#include "GameWorld.h"

Vehicle::Vehicle(GameWorld *world) : m_world(world), m_steering(new SteeringBehavior(this))
{
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
	m_pos.wrap_around(-m_world->width() / 2, m_world->width() / 2, -m_world->height() / 2, m_world->height() / 2);
}


void Vehicle::render(HDC hdc) {
	TCHAR buf[512];
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	long cx = tm.tmAveCharWidth;
	long cy = tm.tmHeight + tm.tmExternalLeading;
	TextOut(hdc, -m_world->width()/2+cx, -m_world->height()/2+cy, buf, wsprintf(buf, TEXT("Position of the vehicle is (%d, %d)"), m_pos.x(), m_pos.y()));
	Ellipse(hdc, m_pos.x() - 5, m_pos.y() - 5, m_pos.x() + 5, m_pos.y() + 5);
}