#pragma once
#include <list>
#include "Vector2D.h"

class Path
{
	std::list<Vector2D> m_point_list;
	std::list<Vector2D>::iterator m_iter;
	bool m_loop; // true if the path defined by the points is looped
public:
	Path(bool loop=false);
	~Path();
	size_t size() const { return m_point_list.size(); }
	std::list<Vector2D>::iterator begin() { return m_point_list.begin(); }
	std::list<Vector2D>::iterator end() { return m_point_list.end(); }
	Vector2D current_way_point() const { return *m_iter; }
	void set_next_way_point() { ++m_iter; if (m_iter == m_point_list.end()) m_iter = m_point_list.begin(); }
	bool finished() const { if (m_loop) return false; std::list<Vector2D>::iterator it = m_iter; ++it; return it == m_point_list.end(); }
};

