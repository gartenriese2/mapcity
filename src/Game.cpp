#include "Game.hpp"

Game::Game(int windowWidth, int windowHeight, int mapWidth, int mapHeight) {
	
	m_window = new Window(windowWidth, windowHeight);
	m_window->initCam(windowWidth, windowHeight);

	m_world = new World(mapHeight, mapWidth);

	m_window->setWorld(m_world);
	m_world->setCamera(m_window->getCam());

}	

void Game::start() {
	m_window->loop();
}