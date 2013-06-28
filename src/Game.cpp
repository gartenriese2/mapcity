#include "Game.hpp"

Game::Game(int windowWidth, int windowHeight, int mapWidth, int mapHeight) {
	
	m_window = make_shared<Window>(windowWidth, windowHeight);
	m_window->initCam(windowWidth, windowHeight);

	//m_world = new World(mapHeight, mapWidth);
	m_world = make_shared<World>(mapHeight, mapWidth);
	m_window->setWorld(m_world);

}	

void Game::start() {
	m_window->loop();
}