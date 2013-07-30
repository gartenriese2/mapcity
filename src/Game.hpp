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

		void end();

		const World & getWorld() const { return * m_world; }
		const Window & getWindow() const { return * m_window; }
		
	private:
		
		shared_ptr<World> m_world;
		shared_ptr<Window> m_window;

		thread m_graphicsThread;
		thread m_timeThread;
		thread m_simulationThread;
		bool m_isRunning;

		void initGraphics(int, int);
		void initTime();
		void initSimulation(int, int);

};

#endif