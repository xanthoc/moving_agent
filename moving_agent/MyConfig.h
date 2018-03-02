#pragma once
class MyConfig
{
	int m_time_quantum; // the min time interval for waiting
	int m_time_delta; // the time interval between each calc in msec

	MyConfig();
	~MyConfig();
public:
	static MyConfig& instance();
	int time_quantum() const { return m_time_quantum; }
	int time_delta() const { return m_time_delta; }
	void set_time_quantum(int val) { m_time_quantum = val; }
	void set_time_delta(int val) { m_time_delta = val; }
};
#define my_config MyConfig::instance()

