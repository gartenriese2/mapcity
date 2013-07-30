#include "Game.hpp"

Game::Game(const int windowWidth, const int windowHeight, const int mapWidth, const int mapHeight) {

	m_graphicsThread = thread(&Game::initGraphics, this, windowWidth, windowHeight);

	while(!m_isRunning);

	m_simulationThread = thread(&Game::initSimulation, this, mapWidth, mapHeight);

	m_timeThread = thread(&Game::initTime, this);

}

Game::~Game() {

}

void Game::end() {
	
	m_graphicsThread.join();
	m_timeThread.join();
	m_simulationThread.join();
	
}

void Game::initGraphics(const int width, const int height) {

	m_window = make_shared<Window>(width, height);
	m_window->initCam(width, height);
	
	m_isRunning = true;
	m_window->loop();
	m_isRunning = false;
	
}

void Game::initTime() {

	Time::instance().printTime(m_isRunning);

}

void Game::initSimulation(const int width, const int height) {

	m_world = make_shared<World>(height, width);
	m_world->loop(m_isRunning);

}