#ifndef GAME_HPP
#define GAME_HPP

#include "World.hpp"
#include "Window.hpp"
#include "Time.hpp"

#include <memory>
#include <thread>

class Game {
	
	public:
		
		Game(int, int, int, int);
		~Game();

		void start();

		shared_ptr<World> getWorld() { return m_world; }
		shared_ptr<Window> getWindow() { return m_window; }
		
	private:
		
		shared_ptr<World> m_world;
		shared_ptr<Window> m_window;

		thread m_graphicsThread;
		thread m_timeThread;
		bool m_isRunning;

		void initGraphics(int, int);
		void initTime();

};

#endif