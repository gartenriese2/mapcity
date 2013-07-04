#ifndef TIME_HPP
#define TIME_HPP

#include "ogl.h"
#include <deque>

const int numTimes = 10;

class Time {
	
	public:
		
		Time();
		
		void start() const;
		void end() const;
		void waitAndAdd();
		double getAverage() const;
	
	private:
		
		std::deque<double> m_lastTimes;
		unsigned int m_queryID[2];
};

#endif