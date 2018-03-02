#include "stdafx.h"
#include "MyConfig.h"


MyConfig::MyConfig() : m_time_quantum(10), m_time_delta(100)
{
}


MyConfig::~MyConfig()
{
}

MyConfig& MyConfig::instance() {
	static MyConfig ins;
	return ins;
}
