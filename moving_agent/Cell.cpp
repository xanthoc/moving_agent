#include "stdafx.h"
#include "Cell.h"


Cell::Cell(const Vector2D &top_left, const Vector2D &bottom_right) : m_tl(top_left), m_br(bottom_right)
{
}


Cell::~Cell()
{
}

bool Cell::is_overlapped(const Vector2D &tl, const Vector2D &br) const {
	bool x_overlap = !(m_tl.m_x > br.m_x || m_br.m_x < tl.m_x);
	bool y_overlap = !(m_tl.m_y > br.m_y || m_br.m_y < tl.m_y);
	return x_overlap && y_overlap;
}

void Cell::tag_neighbor(const Vehicle *ob, double range) const {
	for (auto iter = m_members.begin(); iter != m_members.end(); ++iter) {
		if (ob == *iter) continue;
		Vector2D to = (*iter)->pos() - ob->pos();
		double dist = to.length() - (*iter)->bounding_radius();
		if (dist < range) (*iter)->tag();
	}
}
