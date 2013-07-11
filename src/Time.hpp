#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <mutex>
#include <iostream>
#include <assert.h>

using namespace std::chrono;

class Time {
	public:
		
		static Time& instance();
		long getStartTime() const;
		long getSecondsSinceStart() const;
		void waitMilliseconds(unsigned int) const;

		void setIngameTime();
		void setIngameSpeed(unsigned int);
		unsigned long getIngameTime();
		unsigned long getIngameTimeSeconds() { return getIngameTime() / 1000000000; }
		unsigned long getIngameTimeHours() { return getIngameTimeSeconds() / 3600; }
		unsigned long getIngameTimeDays() { return getIngameTimeHours() / 24; }

		void printEachHour(bool &);

		static const unsigned long PAUSE = 0;
		static const unsigned long REALTIME = 1;
		static const unsigned long NORMAL = 60;
		static const unsigned long FAST = 3600;
		static const unsigned long FASTFORWARD = 86400;
		

	protected:
		
		static Time* pInstance;

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

		time_point<system_clock> m_startTime;
		unsigned long m_ingameTime;
		unsigned int m_ingameSpeed;
		time_point<system_clock> m_lastTimeSet;

};

#endif