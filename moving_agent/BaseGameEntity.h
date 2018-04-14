#pragma once
#include "Vector2D.h"

class BaseGameEntity
{
protected:
	Vector2D m_pos;
	Vector2D m_scale;
public:
	BaseGameEntity();
	virtual ~BaseGameEntity();
	Vector2D& pos() { return m_pos; }
	Vector2D& scale() { return m_scale; }
};

