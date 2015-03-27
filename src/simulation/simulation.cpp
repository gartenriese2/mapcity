#include "simulation.hpp"

/**************************************************************************************************/

Simulation::Simulation()
  : m_timepoint{std::chrono::system_clock::now()}
{}

/**************************************************************************************************/

UpdatableManager & Simulation::getUpdatableManager() {
	return m_manager;
}

/**************************************************************************************************/

void Simulation::update() {
	std::chrono::duration<float> elapsed_seconds = std::chrono::system_clock::now() - m_timepoint;
	m_manager.update(elapsed_seconds.count());
	m_timepoint = std::chrono::system_clock::now();
}

/**************************************************************************************************/
