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
			unsigned long qID = h.getQueriedID();
			if (qID != 0) m_map->getHexagonByID(qID).query();
			h.query();
			h.setQueriedID(h.getID());
		} catch (const char * msg) {
			std::cout << msg << std::endl;
		}
	}
	
}