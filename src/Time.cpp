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
}

Time::~Time() {

}

long Time::getStartTime() {

	std::lock_guard<std::mutex> guard(sMutex);
	return m_startTime.time_since_epoch().count();

}

long Time::getSecondsSinceStart() {

	std::lock_guard<std::mutex> guard(sMutex);
	auto t = system_clock::now().time_since_epoch() - m_startTime.time_since_epoch();
	return duration_cast<seconds>(t).count();

}

void Time::waitMilliseconds(const unsigned int ms) {

	auto t = system_clock::now().time_since_epoch();
	unsigned int since = 0;
	while(since < ms) {
		since = duration_cast<milliseconds>(system_clock::now().time_since_epoch() - t).count();
	}

}