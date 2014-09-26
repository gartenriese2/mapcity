#include "graphics.hpp"

constexpr unsigned int k_defaultWidth {1280};
constexpr unsigned int k_defaultHeight {720};

void Graphics::init() {

	m_enginePtr = std::make_unique<Engine>();
	m_windowPtr = std::make_unique<WindowID>(
		m_enginePtr->createWindow(k_defaultWidth, k_defaultHeight)
	);

}
