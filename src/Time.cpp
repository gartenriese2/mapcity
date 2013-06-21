#include "Time.hpp"

Time::Time() {
	glGenQueries(2, m_queryID);
}

void Time::start() {
	glQueryCounter(m_queryID[0], GL_TIMESTAMP);
}

void Time::end() {
	glQueryCounter(m_queryID[1], GL_TIMESTAMP);
}

void Time::waitAndAdd() {
	GLint stopTimerAvailable = 0;
	GLuint64 startTime, stopTime;
	while (!stopTimerAvailable) {
	    glGetQueryObjectiv(m_queryID[1], GL_QUERY_RESULT_AVAILABLE, &stopTimerAvailable);
	}
	glGetQueryObjectui64v(m_queryID[0], GL_QUERY_RESULT, &startTime);
	glGetQueryObjectui64v(m_queryID[1], GL_QUERY_RESULT, &stopTime);
	m_lastTimes.push_back((stopTime - startTime) / 1000000.0);
	if (m_lastTimes.size() > numTimes) {
		m_lastTimes.pop_front();
	}
}

double Time::getAverage() {
	double avg = 0.0;
	for (auto i : m_lastTimes) {
		avg += i;
	}
	return avg / static_cast<double>(numTimes);
}