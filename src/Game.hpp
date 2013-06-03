#ifndef GAME_HPP
#define GAME_HPP

#include "World.hpp"
#include "Window.hpp"

class Game {
public:
	Game(int, int, int, int);

	void start();

	inline World * getWorld() { return m_world; }
	inline Window * getWindow() { return m_window; }
	
private:
	World * m_world;
	Window * m_window;
	
};

#endif