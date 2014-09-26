#include "Graphics.hpp"

Graphics * Graphics::pInstance = nullptr;

Graphics & Graphics::instance() {
	
	static Cleanup cleanup;
	
	if (pInstance == nullptr) {
		pInstance = new Graphics();
	}
	
	return * pInstance;
}

Graphics::Cleanup::~Cleanup() {
	
	delete Graphics::pInstance;
	Graphics::pInstance = nullptr;

}

Graphics::Graphics() {
	
}

Graphics::~Graphics() {

}

void Graphics::setDimensions(const unsigned int w, const unsigned int h) {

	m_windowWidth = w < MIN_WIDTH ? MIN_WIDTH : w > MAX_WIDTH ? MAX_WIDTH : w;
	m_windowHeight = h < MIN_HEIGHT ? MIN_HEIGHT : h > MAX_HEIGHT ? MAX_HEIGHT : w;

}

void Graphics::init() {

	m_window = make_shared<Window>(m_windowWidth, m_windowHeight);
	m_window->initCam(m_windowWidth, m_windowHeight);

}

void Graphics::loop() {

	m_window->loop();

}