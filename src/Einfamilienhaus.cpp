#include "Einfamilienhaus.hpp"

Einfamilienhaus::Einfamilienhaus(glm::vec3 center, glm::vec3 front, glm::vec3 side) {

	setShape(center, front, side);
	setHeight(k_minHeight, k_maxHeight);
	
	createObject();
	createHouseholds(k_numHouseholds);


}

Einfamilienhaus::~Einfamilienhaus() {
	
}

EinfamilienhausZone::EinfamilienhausZone(std::vector<glm::vec3> bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

EinfamilienhausZone::~EinfamilienhausZone() {
	
}