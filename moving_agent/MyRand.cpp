#include "stdafx.h"
#include "MyRand.h"
#include <ctime>


MyRand::MyRand()
{
	srand(static_cast<unsigned int>(time(nullptr)));
}


MyRand::~MyRand()
{
}

MyRand& MyRand::instance() {
	static MyRand ins;
	return ins;
}