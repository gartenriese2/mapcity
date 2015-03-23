#include "input.hpp"

/**************************************************************************************************/

Input::Input(std::unique_ptr<core::Input> & inputPtr)
  : m_engineInputPtr{inputPtr},
	m_leftMouseButtonDown{false},
	m_leftMouseButtonRelease{false}
{
	m_engineInputPtr->addMouseCursorFunc([&](const double x, const double y){
		m_mousePos = {static_cast<unsigned int>(x), static_cast<unsigned int>(y)};
	});
	m_engineInputPtr->addMouseButtonFunc([&](const int button, const int action, const int){
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			m_leftMouseButtonDown = true;
			m_leftMouseButtonDownPos = m_mousePos;
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
			m_leftMouseButtonRelease = true;
			m_leftMouseButtonReleasePos = m_mousePos;
		}
	});
	m_engineInputPtr->addMouseScrollFunc([&](const double, const double yoffset){
		m_scrollOffset += yoffset;
	});
}

/**************************************************************************************************/

const glm::uvec2 & Input::getMousePos() const {
	return m_mousePos;
}

/**************************************************************************************************/

bool Input::hasLeftClicked() {
	if (m_leftMouseButtonRelease) {
		m_leftMouseButtonRelease = false;
		m_leftMouseButtonDown = false;
		return true;
	}
	return m_leftMouseButtonDown;
}

/**************************************************************************************************/
