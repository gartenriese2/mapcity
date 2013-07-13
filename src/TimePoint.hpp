#ifndef TIMEPOINT_HPP
#define TIMEPOINT_HPP

#include <iostream>

class TimePoint {
	
	public:

		TimePoint(unsigned long);
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
		TimePoint & operator+=(const TimePoint &);
		TimePoint & operator=(const TimePoint &);

		unsigned long getTimeInSeconds() const;
		unsigned long getTimeInMinutes() const;
		unsigned long getTimeInHours() const;
		unsigned long getTimeInDays() const;

	protected:

		std::string getTimeStamp() const;

	private:

		unsigned long m_timePoint;

};

#endif