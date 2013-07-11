#include "Time.hpp"

Time* Time::pInstance = nullptr;
std::mutex Time::sMutex;

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
	m_ingameTime = 0;
	m_lastTimeSet = system_clock::now();
}

Time::~Time() {

}

long Time::getStartTime() const {

	std::lock_guard<std::mutex> guard(sMutex);

	return m_startTime.time_since_epoch().count();

}

long Time::getSecondsSinceStart() const {

	std::lock_guard<std::mutex> guard(sMutex);

	auto t = system_clock::now().time_since_epoch() - m_startTime.time_since_epoch();
	return duration_cast<seconds>(t).count();

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
	m_ingameTime += m_ingameSpeed * t.count();
	m_lastTimeSet = system_clock::now();

}

unsigned long Time::getIngameTime() {

	setIngameTime();
	return m_ingameTime;

}

void Time::setIngameSpeed(const unsigned int set) {

	assert(set == PAUSE || set == REALTIME || set == NORMAL || set == FAST || set == FASTFORWARD);
	
	setIngameTime();
	m_ingameSpeed = set;

}

void Time::printEachHour(bool & isRunning) {

	unsigned int second = getIngameTimeSeconds();
	unsigned int minute = getIngameTimeSeconds() / 60;
	unsigned int hour = getIngameTimeHours();
	unsigned int day = getIngameTimeDays();
	unsigned int dailyHour = hour;
	unsigned int hourlyMinute = minute;
	unsigned int minutelySecond = second;

	while (isRunning) {
		
		if (m_ingameSpeed == FASTFORWARD) {
			
			if (getIngameTimeDays() > day) {
				std::cout << "Day " << ++day << "\n";
			}

			hour = getIngameTimeHours() % 24;
			minute = (getIngameTimeSeconds() / 60) % 60;
			second = getIngameTimeSeconds() % 60;

		} else if (m_ingameSpeed == FAST) {			
			
			dailyHour = getIngameTimeHours() % 24;

			if (dailyHour > hour) {
				
				std::cout << ++hour << ":00 of day " << getIngameTimeDays() << "\n";

			} else if (dailyHour == 0 && hour == 23) {
				
				std::cout << "Midnight of day " << getIngameTimeDays() << "!\n";
				hour = 0;
				day++;
				
			}

			minute = (getIngameTimeSeconds() / 60) % 60;
			second = getIngameTimeSeconds() % 60;

		} else if (m_ingameSpeed == NORMAL) {
			
			hourlyMinute = (getIngameTimeSeconds() / 60) % 60;

			if (hourlyMinute > minute) {
				
				if (minute < 9) {
					std::cout << getIngameTimeHours() % 24 << ":0" << ++minute << " of day " << getIngameTimeDays() << "\n";
				} else {
					std::cout << getIngameTimeHours() % 24 << ":" << ++minute << " of day " << getIngameTimeDays() << "\n";
				}

			} else if (hourlyMinute == 0 && minute == 59) {
				
				std::cout << getIngameTimeHours() % 24 << ":00" << " of day " << getIngameTimeDays() << "\n";
				minute = 0;
				hour++;
				if (hour == 24) {
					hour = 0;
					day++;
				}

			}

			second = getIngameTimeSeconds() % 60;

		} else if (m_ingameSpeed == REALTIME) {

			minutelySecond = getIngameTimeSeconds() % 60;

			if (minutelySecond > second) {
				
				if (second < 9 && minute < 9) {
					std::cout << getIngameTimeHours() % 24 << ":0" << minute << ":0" << ++second << " of day " << getIngameTimeDays() << "\n";
				} else if (minute < 9) {
					std::cout << getIngameTimeHours() % 24 << ":0" << minute << ":" << ++second << " of day " << getIngameTimeDays() << "\n";
				} else if (second < 9) {
					std::cout << getIngameTimeHours() % 24 << ":" << minute << ":0" << ++second << " of day " << getIngameTimeDays() << "\n";
				} else {
					std::cout << getIngameTimeHours() % 24 << ":" << minute << ":" << ++second << " of day " << getIngameTimeDays() << "\n";
				}

			} else if (minutelySecond == 0 && second == 59 && minute == 59) {
				
				std::cout << getIngameTimeHours() % 24 << ":00:00" << " of day " << getIngameTimeDays() << "\n";
				second = 0;
				minute = 0;
				hour++;
				if (hour == 24) {
					hour = 0;
					day++;
				}

			} else if (minutelySecond == 0 && second == 59) {
				
				std::cout << getIngameTimeHours() % 24 << ":" << ++minute << ":00" << " of day " << getIngameTimeDays() << "\n";
				second = 0;

			}

		}

	}

}