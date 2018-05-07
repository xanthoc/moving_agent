#pragma once
#include "BaseGameEntity.h"

class Obstacle : public BaseGameEntity
{
public:
	Obstacle(const Vector2D pos, double br) : BaseGameEntity(pos, br) {}
	~Obstacle() {}
	void update(double elapsed_time) {}
	void render(HDC hdc) {
		Ellipse(hdc, static_cast<int>(m_pos.x() - m_bounding_radius), static_cast<int>(m_pos.y() - m_bounding_radius), 
			static_cast<int>(m_pos.x() + m_bounding_radius), static_cast<int>(m_pos.y() + m_bounding_radius));
	}
};

