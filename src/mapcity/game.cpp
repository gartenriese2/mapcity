#include "game.hpp"

void Game::initGraphics() {

	m_graphicsPtr = std::make_unique<Graphics>();
	m_graphicsPtr->init();

}

bool Game::graphicsShouldClose() const {

	if (!m_graphicsPtr) return false;
	return m_graphicsPtr->shouldClose();

}

void Game::terminateGraphics() {

	if (m_graphicsPtr) {
		m_graphicsPtr->terminate();
		m_graphicsPtr.reset();
	}

}
