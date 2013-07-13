#include "TimePoint.hpp"

TimePoint::TimePoint(const unsigned long time, const unsigned int year) {

	m_timePoint = time;
	m_startYear = year;
	std::cout << "constructor " << year << "\n";

}

TimePoint::TimePoint() {

	m_timePoint = 0;
	m_startYear = 0;

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
	assert(lhs.m_startYear == rhs.m_startYear);
	return TimePoint(lhs.m_timePoint + rhs.m_timePoint, lhs.m_startYear);
}

const TimePoint operator-(const TimePoint & lhs, const TimePoint & rhs) {
	assert(lhs.m_startYear == rhs.m_startYear);
	return TimePoint(lhs.m_timePoint - rhs.m_timePoint, lhs.m_startYear);
}

TimePoint & TimePoint::operator+=(const TimePoint & rhs) {
	m_timePoint += rhs.m_timePoint;
	return *this;
}

TimePoint & TimePoint::operator+=(const unsigned long rhs) {
	m_timePoint += rhs;
	return *this;
}

TimePoint & TimePoint::operator=(const TimePoint & rhs) {
	m_timePoint = rhs.m_timePoint;
	m_startYear = rhs.m_startYear;
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

	std::string month(std::to_string(getMonth()));
	if (std::stoi(month) < 10) month = "0" + month;
	std::string days(std::to_string(getTimeInDays() + 1));
	std::string hours(std::to_string(getTimeInHours() % 24));
	if (std::stoi(hours) < 10) hours = "0" + hours;
	std::string minutes(std::to_string(getTimeInMinutes() % 60));
	if (std::stoi(minutes) < 10) minutes = "0" + minutes;
	std::string seconds(std::to_string(getTimeInSeconds() % 60));
	if (std::stoi(seconds) < 10) seconds = "0" + seconds;

	return month + "." + std::to_string(getYear()) + ", Day " + days + ", " + hours + ":" + minutes + ":" + seconds;

}

unsigned int TimePoint::getYear() const {

	// 366 + 365 + 365 + 365
	unsigned int fourYears = 1461;
	unsigned int firstYear = 366;

	unsigned int year = (getTimeInDays() / fourYears) * 4;
	unsigned int remainder = getTimeInDays() % fourYears;

	if (remainder < firstYear) {
		
		return year + m_startYear;

	} else {
		
		remainder -= firstYear;
		year++;
		while (remainder >= 365) {
			year++;
			remainder += 365;
		}

	}

	return year + m_startYear;

}

void TimePoint::setYear(const unsigned int year) {
	m_startYear = year;
}

bool TimePoint::isLeapYear() const {
	return (getYear() - m_startYear) % 4 == 0;
}

unsigned int TimePoint::getMonth() const {

	unsigned int fourYears = 1461;
	unsigned int remainder = getTimeInDays() % fourYears;

	if (isLeapYear()) {
		
		if (remainder < 31) return 1;
		else if (remainder < 60) return 2;
		else if (remainder < 91) return 3;
		else if (remainder < 121) return 4;
		else if (remainder < 152) return 5;
		else if (remainder < 182) return 6;
		else if (remainder < 213) return 7;
		else if (remainder < 244) return 8;
		else if (remainder < 274) return 9;
		else if (remainder < 305) return 10;
		else if (remainder < 335) return 11;
		else return 12;

	} else {
		
		remainder = (remainder - 366) % 365;

		if (remainder < 31) return 1;
		else if (remainder < 59) return 2;
		else if (remainder < 90) return 3;
		else if (remainder < 120) return 4;
		else if (remainder < 151) return 5;
		else if (remainder < 181) return 6;
		else if (remainder < 212) return 7;
		else if (remainder < 243) return 8;
		else if (remainder < 273) return 9;
		else if (remainder < 304) return 10;
		else if (remainder < 334) return 11;
		else return 12;

	}

	return 0;

}