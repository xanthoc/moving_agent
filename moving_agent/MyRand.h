#pragma once
class MyRand
{
	MyRand();
	~MyRand();
public:
	static MyRand& instance();
	// returns from 0.0 to 1.0
	double drand() const {
		double tmp = rand();
		return tmp / RAND_MAX;
	}
	// returns from low to high
	double drand(double low, double high) {
		return low + drand()*(high - low);
	}
};
#define my_rand MyRand::instance()

