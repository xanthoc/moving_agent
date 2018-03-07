#pragma once
#include "Vector2D.h"

class BaseGameEntity
{
protected:
	Vector2D m_pos;
public:
	BaseGameEntity();
	virtual ~BaseGameEntity();
	Vector2D& pos() { return m_pos; }
};

