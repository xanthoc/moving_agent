#include "stdafx.h"
#include "Path.h"
#include "MyRand.h"


Path::Path(bool loop) : m_loop(loop) {
	m_point_list.push_back(Vector2D(100, 100));
	m_point_list.push_back(Vector2D(100, 200));
	m_point_list.push_back(Vector2D(300, 300));
	m_point_list.push_back(Vector2D(500, 250));
	m_iter = m_point_list.begin();
	m_loop = true;
}


Path::~Path() {
}
