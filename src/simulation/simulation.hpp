#pragma once

#include "updatablemanager.hpp"

class Simulation {

	public:

		Simulation() {}

		UpdatableManager & getUpdatableManager();

		void update(float);

	private:

		UpdatableManager m_manager;

};
