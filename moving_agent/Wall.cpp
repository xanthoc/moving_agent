#include "stdafx.h"
#include "Wall.h"
#include "MyGDI.h"

void Wall::render() {
	my_gdi.draw_wall(m_from, m_to, 10);
}
