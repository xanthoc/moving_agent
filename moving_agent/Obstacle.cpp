#include "stdafx.h"
#include "Obstacle.h"
#include "MyGDI.h"

void Obstacle::render() {
	if (m_tag) my_gdi.draw_light_gray_circle(m_pos, m_bounding_radius);
	else my_gdi.draw_gray_circle(m_pos, m_bounding_radius);
}

