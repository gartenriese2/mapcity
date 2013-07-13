#include "Time.hpp"

Time * Time::pInstance = nullptr;
std::mutex Time::sMutex;
std::mutex Time::s_getMutex;

Time& Time::instance() {
	
	static Cleanup cleanup;
	std::lock_guard<std::mutex> guard(sMutex);
	if (pInstance == nullptr) {
		pInstance = new Time();
	}
	
	return *pInstance;
}

Time::Cleanup::~Cleanup() {
	std::lock_guard<std::mutex> gaurd(Time::sMutex);
	delete Time::pInstance;
	Time::pInstance = nullptr;
}

Time::Time() {
	m_startTime = system_clock::now();
	m_ingameSpeed = 1;
	m_lastTimeSet = system_clock::now();
	
	m_ingameTime = TimePoint(0, sk_startYear);

}

Time::~Time() {

}

TimePoint Time::getStartTime() const {

	std::lock_guard<std::mutex> guard(s_getMutex);

	return TimePoint(m_startTime.time_since_epoch().count(), 0);

}

unsigned long Time::getSecondsSinceStart() const {

	std::lock_guard<std::mutex> guard(s_getMutex);

	auto t = system_clock::now().time_since_epoch() - m_startTime.time_since_epoch();
	return duration_cast<seconds>(t).count();

}

unsigned long Time::getSecondsSinceTimePoint(const TimePoint & tp) {

	long sec = getIngameTime().getTimeInSeconds() - tp.getTimeInSeconds();
	assert (sec >= 0);
	return sec;

}

void Time::waitMilliseconds(const unsigned int ms) const {

	std::lock_guard<std::mutex> guard(sMutex);

	auto t = system_clock::now().time_since_epoch();
	unsigned int since = 0;
	while(since < ms) {
		since = duration_cast<milliseconds>(system_clock::now().time_since_epoch() - t).count();
	}

}

void Time::setIngameTime() {

	std::lock_guard<std::mutex> guard(sMutex);

	auto t = system_clock::now().time_since_epoch() - m_lastTimeSet.time_since_epoch();
	assert(t.count() >= 0);
	m_ingameTime += (m_ingameSpeed * t.count());
	m_lastTimeSet = system_clock::now();

}

TimePoint & Time::getIngameTime() {

	std::lock_guard<std::mutex> guard(s_getMutex);

	setIngameTime();
	return m_ingameTime;

}

void Time::setIngameSpeed(const unsigned int set) {

	assert(set == PAUSE || set == REALTIME || set == NORMAL || set == FAST || set == FASTFORWARD);
	
	setIngameTime();
	m_ingameSpeed = set;

}

void Time::printTime(bool & isRunning) {

	setIngameTime();
	unsigned int second = m_ingameTime.getTimeInSeconds();
	unsigned int minute = m_ingameTime.getTimeInMinutes();
	unsigned int hour = m_ingameTime.getTimeInHours();
	unsigned int day = m_ingameTime.getTimeInDays();
	unsigned int dailyHour = hour;
	unsigned int hourlyMinute = minute;
	unsigned int minutelySecond = second;

	while (isRunning) {
		
		setIngameTime();

		if (m_ingameSpeed == FASTFORWARD) {
			
			if (m_ingameTime.getTimeInDays() > day) {
				
				day++;
				std::cout << m_ingameTime << "\n";

			}

			hour = m_ingameTime.getTimeInHours() % 24;
			minute = m_ingameTime.getTimeInMinutes() % 60;
			second = m_ingameTime.getTimeInSeconds() % 60;

		} else if (m_ingameSpeed == FAST) {			
			
			dailyHour = m_ingameTime.getTimeInHours() % 24;

			if (dailyHour > hour) {
				
				hour++;
				std::cout << m_ingameTime << "\n";

			} else if (dailyHour == 0 && hour == 23) {
				
				hour = 0;
				day++;
				std::cout << m_ingameTime << "\n";
				
			}

			minute = m_ingameTime.getTimeInMinutes() % 60;
			second = m_ingameTime.getTimeInSeconds() % 60;

		} else if (m_ingameSpeed == NORMAL) {
			
			hourlyMinute = m_ingameTime.getTimeInMinutes() % 60;

			if (hourlyMinute > minute) {
				
				minute++;
				std::cout << m_ingameTime << "\n";

			} else if (hourlyMinute == 0 && minute == 59) {
				
				std::cout << m_ingameTime << "\n";
				
				minute = 0;
				hour++;
				if (hour == 24) {
					hour = 0;
					day++;
				}

			}

			second = m_ingameTime.getTimeInSeconds() % 60;

		} else if (m_ingameSpeed == REALTIME) {

			minutelySecond = m_ingameTime.getTimeInSeconds() % 60;

			if (minutelySecond > second) {
				
				second++;
				std::cout << m_ingameTime << "\n";

			} else if (minutelySecond == 0 && second == 59 && minute == 59) {
				
				std::cout << m_ingameTime << "\n";
				second = 0;
				minute = 0;
				hour++;
				if (hour == 24) {
					hour = 0;
					day++;
				}

			} else if (minutelySecond == 0 && second == 59) {
				
				minute++;
				std::cout << m_ingameTime << "\n";
				second = 0;

			}

		}

	}

}