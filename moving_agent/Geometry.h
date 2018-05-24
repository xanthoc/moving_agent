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

int orientation(const Vector2D &p1, const Vector2D &p2, const Vector2D &p3) {
	// think of cross product of two vectors: p1p2, p2p3
	double val = (p2.m_x - p1.m_x)*(p3.m_y - p2.m_y) - (p3.m_x - p2.m_x)*(p2.m_y - p1.m_y);
	if (val == 0.0) return 0; // colinear
	return val < 0.0 ? 1 : -1; // 1: clockwise, -1: counter clockwise
}

Vector2D find_intersection(const Vector2D &p1, const Vector2D &q1, const Vector2D &p2, const Vector2D &q2) {
	//a1x + b1y = c1
	double a1 = q1.m_y - p1.m_y;
	double b1 = p1.m_x - q1.m_x;
	double c1 = a1*p1.m_x + b1*p1.m_y;
	//a2x + b2y = c2
	double a2 = q2.m_y - p2.m_y;
	double b2 = p2.m_x - q2.m_x;
	double c2 = a2*p2.m_x + b2*p2.m_y;

	double det = a1*b2 - a2*b1;
	assert(det != 0.0);
	//if (det == 0.0) return Vector2D(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
	double x = (c1*b2 - c2*b1)/det;
	double y = (a1*c2 - a2*c1)/det;
	return Vector2D(x, y);
}

bool on_segment(const Vector2D &p, const Vector2D &q, const Vector2D &r) {
	return min(p.m_x, q.m_x) <= r.m_x && r.m_x <= max(p.m_x, q.m_x) && min(p.m_y, q.m_y) <= r.m_y && r.m_y <= max(p.m_y, q.m_y);
}

bool intersect_two_lines(const Vector2D &p1, const Vector2D &q1, const Vector2D &p2, const Vector2D &q2, Vector2D &pt) {
	int o11 = orientation(p1, q1, p2);
	int o12 = orientation(p1, q1, q2);
	int o21 = orientation(p2, q2, p1);
	int o22 = orientation(p2, q2, q1);

	if (o11 != o12 && o21 != o22) {
		pt = find_intersection(p1, q1, p2, q2);
		return true;
	}
	if (o11 == 0 && on_segment(p1, q1, p2)) {
		pt = p2;
		return true;
	}
	if (o12 == 0 && on_segment(p1, q1, q2)) {
		pt = q2;
		return true;
	}
	if (o21 == 0 && on_segment(p2, q2, p1)) {
		pt = p1;
		return true;
	}
	if (o22 == 0 && on_segment(p2, q2, q1)) {
		pt = q1;
		return true;
	}
	return false;
}



