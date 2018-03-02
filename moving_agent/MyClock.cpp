#include "stdafx.h"
#include "MyClock.h"


MyClock::MyClock() : m_prev(clock())
{
	m_start = m_prev;
}


MyClock::~MyClock()
{
}

MyClock& MyClock::instance() {
	static MyClock ins;
	return ins;
}
