#include "Game.hpp"

Game::Game(const int windowWidth, const int windowHeight, const int mapWidth, const int mapHeight) {

	m_graphicsThread = thread(&Game::initGraphics, this, windowWidth, windowHeight);

	m_world = make_shared<World>(mapHeight, mapWidth);

	m_timeThread = thread(&Game::initTime, this);

}

Game::~Game() {
	std::cout << "Game ended after " << Time::instance().getSecondsSinceStart() << " seconds!\n";
	std::cout << "Ingame time: " << Time::instance().getIngameTimeSeconds() << " seconds!\n";
}

void Game::start() {
	
	// start simulation
	while(m_isRunning);

	m_graphicsThread.join();
	m_timeThread.join();
	
}

void Game::initGraphics(const int width, const int height) {

	m_window = make_shared<Window>(width, height);
	m_window->initCam(width, height);
	
	m_isRunning = true;
	m_window->loop();
	m_isRunning = false;
	
}

void Game::initTime() {

	Time::instance().printEachHour(m_isRunning);

}