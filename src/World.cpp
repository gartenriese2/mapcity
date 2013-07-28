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
		Hexagon * h;
		bool exist = false;
		try {
			h = & m_map->getCorrespondingHexagon(glm::vec3(click.x,0,click.z));
			exist = true;
		} catch (const char * msg) {
			std::cout << msg << std::endl;
			exist = false;
		}
		if (exist) {
			
			if (m_queriedID != 0) {
				m_map->getHexagonByID(m_queriedID).deselect();
			}
			if (m_queriedID != h->getID()) {
				h->select();
				setQueriedID(h->getID());
			} else {
				setQueriedID(0);
			}
			
		}
	}
	
}