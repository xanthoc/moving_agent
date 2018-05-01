#pragma once
class MyRand
{
	MyRand();
	~MyRand();
public:
	static MyRand& instance();
	double drand() const {
		double tmp = rand();
		return tmp / RAND_MAX;
	}
};
#define my_rand MyRand::instance()

