#pragma once
#include "Vector2D.h"

Vector2D to_world_space(const Vector2D &target, const Vector2D &heading, const Vector2D &side, const Vector2D &pos) {

	Vector2D res = Vector2D(heading.m_x*target.m_x + side.m_x*target.m_y, heading.m_y*target.m_x + side.m_y*target.m_y);
	res += pos;
	return res;
}

Vector2D to_local_space(const Vector2D &target, const Vector2D &heading, const Vector2D &side, const Vector2D &pos) {
	Vector2D res = target - pos;
	res = Vector2D(heading.m_x*res.m_x + heading.m_y*res.m_y, side.m_x*res.m_x + side.m_y*res.m_y);
	return res;
}

bool intersect_two_lines(const Vector2D &p1, const Vector2D &q1, const Vector2D &p2, const Vector2D &q2) {
	return false;
}

double find_intersecting_point(const Vector2D &p1, const Vector2D &q1, const Vector2D &p2, const Vector2D &q2, Vector2D &ipt) {
	ipt = Vector2D(1.0, 2.0);
	return 0.0;
}


