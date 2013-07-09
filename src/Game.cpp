#include "Game.hpp"

Game::Game(const int windowWidth, const int windowHeight, const int mapWidth, const int mapHeight) {

	m_graphicsThread = thread(&Game::initGraphics, this, windowWidth, windowHeight);

	m_world = make_shared<World>(mapHeight, mapWidth);

}

Game::~Game() {
	std::cout << "Game deleted!\n";
}

void Game::start() {
	
	// start simulation
	//m_simulationThread = thread(&Game::initSimulation, this);
	while(m_isRunning);

	std::cout << "Graphics thread joining ...\n";
	m_graphicsThread.join();
	std::cout << "Window closed!\n";
	
}

void Game::initGraphics(const int width, const int height) {

	m_window = make_shared<Window>(width, height);
	m_window->initCam(width, height);
	
	m_isRunning = true;
	m_window->loop();
	m_isRunning = false;
	
}

void Game::initSimulation() {

	while(m_isRunning);
	// m_simulationThread.join();

}