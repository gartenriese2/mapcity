
#ifndef TIME_HPP
#define TIME_HPP

#include "ogl.h"
#include <deque>

const int numTimes = 10;

class Time {
public:
	Time();
	void start();
	void end();
	void waitAndAdd();
	double getAverage();
private:
	std::deque<double> m_lastTimes;
	unsigned int m_queryID[2];
};

#endif