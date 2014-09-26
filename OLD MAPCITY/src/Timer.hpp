#ifndef TIMER_HPP
#define TIMER_HPP

#include "glincludes.hpp"
#include <deque>

const int numTimes = 10;

class Timer {
	
	public:
		
		Timer();
		
		void start() const;
		void end() const;
		void waitAndAdd();
		double getAverage() const;
	
	private:
		
		std::deque<double> m_lastTimes;
		unsigned int m_queryID[2];
};

#endif