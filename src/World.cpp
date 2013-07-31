#include "World.hpp"

World::World(const int height, const int width) {
	
	m_map = std::make_shared<Map>(height, width);
	
}

void World::loop(bool & isRunning) {

	while(isRunning) {
		
		checkInput();

		build();

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
				
				unsigned int res = 0;
				for (auto z : h->getZones()) {
					
					if (z->isResidential()) {
						
						for (auto b : z->getBuildings()) {
							
							res += b->getResidents();

						}

					}

				}
				std::cout << "Residents in this zone: " << res << "\n";

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
				EinfamilienhausZone * ez = new EinfamilienhausZone(z.first);
				h = & m_map->getCorrespondingHexagon(ez->getCenter());
				h->addZone(* ez);
			} else if (z.second == 2) {
				MietshausZone * mz = new MietshausZone(z.first);
				h = & m_map->getCorrespondingHexagon(mz->getCenter());
				h->addZone(* mz);
			} else if (z.second == 3) {
				KleinerLadenZone * klz = new KleinerLadenZone(z.first);
				h = & m_map->getCorrespondingHexagon(klz->getCenter());
				h->addZone(* klz);
			} else if (z.second == 4) {
				GrosserLadenZone * glz = new GrosserLadenZone(z.first);
				h = & m_map->getCorrespondingHexagon(glz->getCenter());
				h->addZone(* glz);
			}

		}

	}

}

void World::build() {

	for (auto h : m_map->getHexaVector()) {

		for (auto z : h.getZones()) {

			if (!z->hasBuildings()) {
				z->addBuilding();
			} else {
				for (auto b : z->getBuildings()) {
					if (b->isUnderConstruction()) b->construct();
				}
			}

		}

	}

}