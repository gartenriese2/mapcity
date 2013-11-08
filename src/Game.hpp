#ifndef GAME_HPP
#define GAME_HPP

#include "Graphics.hpp"
#include "World.hpp"
#include "Time.hpp"

#include <memory>
#include <thread>

class Game {
	
	public:
		
		Game(const int, const int, const int, const int, const bool = true);
		~Game();

		void end();

		// const World & getWorld() const { return * m_world; }
		// const Window & getWindow() const { return * m_window; }
		
	protected:
		
		shared_ptr<World> m_world;
		shared_ptr<Window> m_window;

		thread m_graphicsThread;
		thread m_timeThread;
		thread m_simulationThread;
		bool m_isRunning;
		bool m_graphicsEnabled;

		void initGraphics(int, int);
		void initTime();
		void initSimulation(int, int);

};

#endif