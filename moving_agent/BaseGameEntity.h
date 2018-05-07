#pragma once
#include "Vector2D.h"

class BaseGameEntity
{
protected:
	bool m_tag;
	Vector2D m_pos;
	Vector2D m_scale;
	double m_bounding_radius;
	BaseGameEntity() : m_tag(false), m_scale(Vector2D(1.0, 1.0)), m_bounding_radius(0.0) {}
	BaseGameEntity(const Vector2D &pos, double br) : m_tag(false), m_pos(pos), m_scale(Vector2D(1.0, 1.0)), m_bounding_radius(br) {}
public:
	virtual ~BaseGameEntity() {}
	const Vector2D& pos() const { return m_pos; }
	void set_pos(const Vector2D &val) { m_pos = val; }
	const Vector2D& scale() const { return m_scale; }
	void set_scale(const Vector2D &val) { m_scale = val; }
	double bounding_radius() const { return m_bounding_radius; }
	void set_bounding_radius(double val) { m_bounding_radius = val; }
	bool is_tagged() const { return m_tag == true; }
	void tag() { m_tag = true; }
	void untag() { m_tag = false; }

	virtual void update(double elapsed_time) {}
	virtual void render(HDC hdc) {}
};

