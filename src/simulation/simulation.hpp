#pragma once

#include "updatablemanager.hpp"

#include <chrono>

class Simulation {

	public:

		Simulation();

		UpdatableManager & getUpdatableManager();

		void update();

	private:

		UpdatableManager m_manager;

		std::chrono::time_point<std::chrono::system_clock> m_timepoint;

};
