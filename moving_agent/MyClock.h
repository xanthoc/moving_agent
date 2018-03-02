#pragma once
#include <ctime>

class MyClock
{
	clock_t m_start;
	clock_t m_prev;
	MyClock();
	~MyClock();
public:
	static MyClock& instance();
	clock_t total_msec() const {
		clock_t tmp = clock();
		return (tmp - m_start) * 1000 / CLOCKS_PER_SEC;
	}
	clock_t delta_msec() const {
		clock_t tmp = clock();
		return (tmp - m_prev) * 1000 / CLOCKS_PER_SEC;
	}
	void update() {
		m_prev = clock();
	}
};
#define my_clock MyClock::instance()


