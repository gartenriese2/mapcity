#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <mutex>
#include <iostream>

using namespace std::chrono;

class Time {
	public:
		
		static Time& instance();
		long getStartTime();
		long getSecondsSinceStart();
		void waitMilliseconds(unsigned int);
		

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

};

#endif