#include "graphics.hpp"

#include "../engine/debug.hpp"

constexpr unsigned int k_defaultWidth {1280};
constexpr unsigned int k_defaultHeight {720};

void Graphics::init() {

	m_enginePtr = std::make_unique<Engine>();
	m_windowPtr = std::make_unique<WindowID>(
		m_enginePtr->createWindow(k_defaultWidth, k_defaultHeight)
	);

	m_windowPtr->addKeyEvent(GLFW_KEY_ESCAPE, [&](){
		m_windowPtr->close();
		m_shouldClose = true;
	});

}

void Graphics::terminate() {

	if (m_windowPtr) {
		m_windowPtr->terminate();
		m_windowPtr.reset();
	}

}
	
