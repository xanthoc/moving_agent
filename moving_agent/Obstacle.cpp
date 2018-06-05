#include "stdafx.h"
#include "Obstacle.h"
#include "MyGDI.h"

void Obstacle::render() {
	if (m_tag) {
		//if (m_scale==Vector2D(1.0, 1.0)) my_gdi.draw_circle(m_pos, m_bounding_radius);
		//else if (m_scale==Vector2D(2.0, 2.0)) my_gdi.draw_circle(m_pos, m_bounding_radius);
		//else my_gdi.draw_gray_circle(m_pos, m_bounding_radius);
		my_gdi.draw_gray_circle(m_pos, m_bounding_radius);
	}
	else my_gdi.draw_circle(m_pos, m_bounding_radius);
}

