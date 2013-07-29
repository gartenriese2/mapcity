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

	checkQueries();
	checkNewZones();
	
}

void World::checkQueries() {

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
				resetQueriedID();
			}
			
		}

	}

}

void World::checkNewZones() {

	if (InputHandler::instance().hasNewZones()) {

		zoneVector zones = InputHandler::instance().getZones();
		Hexagon * h;
		for (auto z : zones) {
			
			if (z.second == 1) {
				EinfamilienhausZone ez(z.first);
				h = & m_map->getCorrespondingHexagon(ez.getCenter());
				h->addZone(ez);
			} else if (z.second == 2) {
				MietshausZone mz(z.first);
				h = & m_map->getCorrespondingHexagon(mz.getCenter());
				h->addZone(mz);
			} else if (z.second == 3) {
				KleinerLadenZone klz(z.first);
				h = & m_map->getCorrespondingHexagon(klz.getCenter());
				h->addZone(klz);
			} else if (z.second == 4) {
				GrosserLadenZone glz(z.first);
				h = & m_map->getCorrespondingHexagon(glz.getCenter());
				h->addZone(glz);
			}

		}

	}

}