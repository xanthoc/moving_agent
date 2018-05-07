#include "stdafx.h"
#include "Obstacle.h"
#include "MyGDI.h"

void Obstacle::render() {
	my_gdi.draw_gray_circle(m_pos, m_bounding_radius);
}

