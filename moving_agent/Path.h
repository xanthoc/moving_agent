#pragma once
#include <list>
#include "Vector2D.h"

class Path
{
	std::list<Vector2D> m_point_list;
public:
	Path();
	~Path();
	size_t size() const { return m_point_list.size(); }
	std::list<Vector2D>::iterator begin() { return m_point_list.begin(); }
	std::list<Vector2D>::iterator end() { return m_point_list.end(); }
};

