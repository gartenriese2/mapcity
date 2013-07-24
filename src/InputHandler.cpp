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