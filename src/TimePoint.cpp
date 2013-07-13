#include "TimePoint.hpp"

TimePoint::TimePoint(const unsigned long time) {

	m_timePoint = time;

}

TimePoint::TimePoint() {

	m_timePoint = 0;

}

TimePoint::~TimePoint() {

}

std::ostream & operator<<(std::ostream & ostr, const TimePoint & tp) {

	ostr << tp.getTimeStamp();
	return ostr;

}

bool operator==(const TimePoint & lhs, const TimePoint & rhs) {
	return (lhs.m_timePoint == rhs.m_timePoint);
}

bool operator!=(const TimePoint & lhs, const TimePoint & rhs) {
	return (lhs.m_timePoint != rhs.m_timePoint);
}

bool operator<(const TimePoint & lhs, const TimePoint & rhs) {
	return (lhs.m_timePoint < rhs.m_timePoint);
}

bool operator>(const TimePoint & lhs, const TimePoint & rhs) {
	return (lhs.m_timePoint > rhs.m_timePoint);
}

bool operator<=(const TimePoint & lhs, const TimePoint & rhs) {
	return (lhs.m_timePoint <= rhs.m_timePoint);
}

bool operator>=(const TimePoint & lhs, const TimePoint & rhs) {
	return (lhs.m_timePoint >= rhs.m_timePoint);
}

const TimePoint operator+(const TimePoint & lhs, const TimePoint & rhs) {
	return TimePoint(lhs.m_timePoint + rhs.m_timePoint);
}

const TimePoint operator-(const TimePoint & lhs, const TimePoint & rhs) {
	return TimePoint(lhs.m_timePoint - rhs.m_timePoint);
}

TimePoint & TimePoint::operator+=(const TimePoint & rhs) {
	m_timePoint += rhs.m_timePoint;
	return *this;
}

TimePoint & TimePoint::operator=(const TimePoint & rhs) {
	m_timePoint = rhs.m_timePoint;
	return *this;
}

unsigned long TimePoint::getTimeInSeconds() const {
	return m_timePoint / 1000000000;
}

unsigned long TimePoint::getTimeInMinutes() const {
	return getTimeInSeconds() / 60;
}

unsigned long TimePoint::getTimeInHours() const {
	return getTimeInMinutes() / 60;
}

unsigned long TimePoint::getTimeInDays() const {
	return getTimeInHours() / 24;
}

std::string TimePoint::getTimeStamp() const {

	std::string days(std::to_string(getTimeInDays()));
	std::string hours(std::to_string(getTimeInHours() % 24));
	if (std::stoi(hours) < 10) hours = "0" + hours;
	std::string minutes(std::to_string(getTimeInMinutes() % 60));
	if (std::stoi(minutes) < 10) minutes = "0" + minutes;
	std::string seconds(std::to_string(getTimeInSeconds() % 60));
	if (std::stoi(seconds) < 10) seconds = "0" + seconds;

	return "Day " + days + ", " + hours + ":" + minutes + ":" + seconds;

}