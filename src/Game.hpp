#ifndef GAME_HPP
#define GAME_HPP

#include "World.hpp"
#include "Window.hpp"

#include <memory>

class Game {
public:
	Game(int, int, int, int);

	void start();

	inline shared_ptr<World> getWorld() { return m_world; }
	inline shared_ptr<Window> getWindow() { return m_window; }
	
private:
	shared_ptr<World> m_world;
	shared_ptr<Window> m_window;
	
};

#endif