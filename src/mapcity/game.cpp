#include "game.hpp"

void Game::initGraphics() {

	m_graphicsPtr = std::make_unique<Graphics>();
	m_graphicsPtr->init();

}
