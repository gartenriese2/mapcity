#include "World.hpp"

World::World(const int height, const int width) {
	
	m_map = std::make_shared<Map>(height, width);
	
}

void World::loop(bool & isRunning) {

	while(isRunning) {
		
		checkInput();

	}

}

void World::checkInput() {

	if (InputHandler::instance().hasNewQuery()) {
		glm::vec3 click = InputHandler::instance().getQuery();
		try {
			Hexagon & h = m_map->getCorrespondingHexagon(glm::vec3(click.x,0,click.z));
			h.query();
		} catch (const char * msg) {
			std::cout << msg << std::endl;
		}
	}
	
}