#pragma once
#include <vector>
#include "Vehicle.h"
#include "Vector2D.h"

class Cell
{
	std::vector<Vehicle*> m_members;
	Vector2D m_tl, m_br;
public:
	Cell(const Vector2D &top_left, const Vector2D &bottom_right);
	~Cell();
	void push_back(Vehicle *vehicle) { m_members.push_back(vehicle); }
	void clear() { m_members.clear(); }
	bool is_empty() const { return m_members.empty(); }
	bool is_overlapped(const Vector2D &tl, const Vector2D &br) const;
	void tag_neighbor(const Vehicle *ob, double range) const;
};

