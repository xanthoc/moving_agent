#pragma once
#include "Vector2D.h"

class Wall
{
	Vector2D m_from;
	Vector2D m_to;
	Vector2D m_nv; // normal vector to the wall
public:
	Wall(const Vector2D &from, const Vector2D &to) : m_from(from), m_to(to) {
		m_nv = (to - from).get_normalized().get_perp();
	}
	~Wall() {}
	void render();
	const Vector2D& from() const { return m_from; }
	const Vector2D& to() const { return m_to; }
	const Vector2D& normal() const { return m_nv; }
};

