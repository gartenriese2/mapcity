#include "InputHandler.hpp"

InputHandler* InputHandler::pInstance = nullptr;
std::mutex InputHandler::sMutex;

InputHandler& InputHandler::instance() {
	
	static Cleanup cleanup;
	std::lock_guard<std::mutex> guard(sMutex);
	if (pInstance == nullptr) {
		pInstance = new InputHandler();
	}
	
	return *pInstance;
}

InputHandler::Cleanup::~Cleanup() {
	std::lock_guard<std::mutex> gaurd(InputHandler::sMutex);
	delete InputHandler::pInstance;
	InputHandler::pInstance = nullptr;
}

InputHandler::InputHandler() {
	
}

InputHandler::~InputHandler() {

}

void InputHandler::addQuery(const glm::vec3 & click) {

	std::lock_guard<std::mutex> guard(sMutex);
	m_query = click;
	m_newQuery = true;

}

glm::vec3 InputHandler::getQuery() {

	std::lock_guard<std::mutex> guard(sMutex);
	m_newQuery = false;
	return m_query;

}

bool InputHandler::hasNewQuery() const {

	std::lock_guard<std::mutex> guard(sMutex);
	return m_newQuery;

}

void InputHandler::addZonePoint(const glm::vec3 & p) {

	std::lock_guard<std::mutex> guard(sMutex);

	m_newZone.push_back(p);

}

void InputHandler::addZone(const std::vector<glm::vec3> & outline, int i) {

	std::lock_guard<std::mutex> guard(sMutex);

	// TO DO: assert isConvex
	// TO DO: assert inMap
	// TO DO: different types of zones

	m_zones.push_back(std::pair<std::vector<glm::vec3>, int>(outline,i));

}

void InputHandler::addZone(int i) {

	std::lock_guard<std::mutex> guard(sMutex);

	// TO DO: assert isConvex
	// TO DO: assert inMap
	// TO DO: different types of zones
	
	if (m_newZone.size() > 2) {
		m_zones.push_back(std::pair<std::vector<glm::vec3>, int>(std::move(m_newZone),i));
	}

}

zoneVector InputHandler::getZones() {

	return std::move(m_zones);

}

bool InputHandler::hasNewZones() const {

	return m_zones.size() > 0;

}