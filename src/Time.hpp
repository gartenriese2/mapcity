#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <mutex>
#include <iostream>
#include <assert.h>

#include "TimePoint.hpp"

using namespace std::chrono;

class Time {
	public:
		
		static Time & instance();
		TimePoint getStartTime() const;

		unsigned long getSecondsSinceStart() const;
		unsigned long getSecondsSinceTimePoint(const TimePoint &);
		void waitMilliseconds(unsigned int) const;
		void setIngameTime();
		void setIngameSpeed(unsigned int);
		TimePoint & getIngameTime();

		void printTime(bool &);

		static const unsigned long PAUSE = 0;
		static const unsigned long REALTIME = 1;
		static const unsigned long NORMAL = 60;
		static const unsigned long FAST = 3600;
		static const unsigned long FASTFORWARD = 86400;

		static const unsigned int sk_startYear = 2000;
		
	protected:
		
		static Time * pInstance;

		friend class Cleanup;
		class Cleanup {
			public:
				~Cleanup();
		};
		
	private:

		Time();
		virtual ~Time();
		Time(const Time&);
		Time& operator=(const Time&);
		static std::mutex sMutex;
		static std::mutex s_getMutex;

		time_point<system_clock> m_startTime;
		TimePoint m_ingameTime;
		unsigned int m_ingameSpeed;
		time_point<system_clock> m_lastTimeSet;

};

#endif