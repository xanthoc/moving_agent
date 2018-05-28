#include "stdafx.h"
#include "Path.h"
#include "MyRand.h"


Path::Path() {
	m_point_list.push_back(Vector2D(100, 100));
	m_point_list.push_back(Vector2D(100, 200));
	m_point_list.push_back(Vector2D(300, 300));
}


Path::~Path() {
}
