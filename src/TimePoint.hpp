#ifndef TIMEPOINT_HPP
#define TIMEPOINT_HPP

#include <iostream>
#include <assert.h>

class TimePoint {
	
	public:

		TimePoint(unsigned long, unsigned int);
		TimePoint();
		~TimePoint();

		friend std::ostream& operator<<(std::ostream &, const TimePoint &);

		friend bool operator==(const TimePoint &, const TimePoint &);
		friend bool operator!=(const TimePoint &, const TimePoint &);
		friend bool operator<(const TimePoint &, const TimePoint &);
		friend bool operator>(const TimePoint &, const TimePoint &);
		friend bool operator<=(const TimePoint &, const TimePoint &);
		friend bool operator>=(const TimePoint &, const TimePoint &);

		friend const TimePoint operator+(const TimePoint &, const TimePoint &);
		friend const TimePoint operator-(const TimePoint &, const TimePoint &);
		TimePoint & operator+=(const TimePoint &);
		TimePoint & operator+=(const unsigned long);
		TimePoint & operator=(const TimePoint &);

		unsigned long getTimeInSeconds() const;
		unsigned long getTimeInMinutes() const;
		unsigned long getTimeInHours() const;
		unsigned long getTimeInDays() const;

		void setYear(unsigned int);

	protected:

		std::string getTimeStamp() const;
		bool isLeapYear() const;
		unsigned int getYear() const;
		unsigned int getMonth() const;
		unsigned int getDayOfMonth() const;
		

	private:

		unsigned long m_timePoint;
		unsigned int m_startYear;

};

#endif