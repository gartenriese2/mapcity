#include "Game.hpp"

Game::Game(const int windowWidth, const int windowHeight, const int mapWidth, const int mapHeight) {
	
	m_window = make_shared<Window>(windowWidth, windowHeight);
	m_window->initCam(windowWidth, windowHeight);

	m_world = make_shared<World>(mapHeight, mapWidth);

}	

void Game::start() {
	m_window->loop();
}