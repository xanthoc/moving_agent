#include "stdafx.h"
#include "Wall.h"
#include "MyGDI.h"

Wall::Wall(const Vector2D &from, const Vector2D &to) : m_from(from), m_to(to) {
	m_nv = (to - from).get_normalized().get_perp();
}

Wall::~Wall() {

}

void Wall::render() {
	my_gdi.draw_wall(m_from, m_to, 10);
}
