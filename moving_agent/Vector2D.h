#pragma once
#include <cmath>
#include <cassert>

class Vector2D
{
public:
	double m_x;
	double m_y;
	Vector2D() : m_x(0.0), m_y(0.0) {}
	Vector2D(double x, double y) : m_x(x), m_y(y) {}
	~Vector2D() {}
	double length() const {
		return sqrt(m_x*m_x + m_y*m_y);
	}
	double length_sq() const {
		return m_x*m_x + m_y*m_y;
	}
	void truncate(double val) {
		assert(val > 0.0);
		double len = length();
		if (len > val) {
			m_x *= val/len;
			m_y *= val/len;
		}
	}
	void wrap_around(int left, int right, int bottom, int top) {
		if (m_x > right) m_x = left;
		if (m_x < left) m_x = right;
		if (m_y < top) m_y = bottom;
		if (m_y > bottom) m_y = top;
	}
	Vector2D get_perp() const {
		Vector2D res;
		res.m_x = -m_y;
		res.m_y = m_x;
		return res;
	}
	Vector2D get_normalized() const {
		Vector2D res;
		double len = length();
		assert(len != 0.0);
		res.m_x = m_x / len;
		res.m_y = m_y / len;
		return res;
	}
	Vector2D operator/(double val) {
		assert(val != 0.0);
		Vector2D res;
		res.m_x = m_x / val;
		res.m_y = m_y / val;
		return res;
	}
	Vector2D operator*(double val) {
		Vector2D res;
		res.m_x = m_x * val;
		res.m_y = m_y * val;
		return res;
	}
	Vector2D operator-(const Vector2D &other) const {
		Vector2D res;
		res.m_x = m_x - other.m_x;
		res.m_y = m_y - other.m_y;
		return res;
	}
	Vector2D operator+(const Vector2D &other) const {
		Vector2D res;
		res.m_x = m_x + other.m_x;
		res.m_y = m_y + other.m_y;
		return res;
	}
	Vector2D& operator+=(const Vector2D &other) {
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}
	Vector2D& operator*=(double val) {
		m_x *= val;
		m_y *= val;
		return *this;
	}
	bool operator==(const Vector2D &other) const {
		return (m_x == other.m_x && m_y == other.m_y);
	}
};

