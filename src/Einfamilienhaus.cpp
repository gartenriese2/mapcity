#include "Einfamilienhaus.hpp"

Einfamilienhaus::Einfamilienhaus(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side) {

	setShape(center, front, side);
	setHeight(k_minFloorHeight, k_maxFloorHeight, k_minFloors, k_maxFloors);
	
	createObject();
	createHouseholds(k_numHouseholds);

}

Einfamilienhaus::~Einfamilienhaus() {
	
}

EinfamilienhausZone::EinfamilienhausZone(const vectorVec3 & bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

EinfamilienhausZone::~EinfamilienhausZone() {
	
}

void EinfamilienhausZone::addBuilding() {

	// calculate center & shape for new building
	// create building and add it to vector

	glm::vec3 sideDir = glm::vec3(0,0,-1);
	glm::vec3 frontDir = glm::vec3(1,0,0);
	glm::vec3 side = sideDir * Einfamilienhaus::getMinWidth() / 2.0f;
	glm::vec3 front = frontDir * Einfamilienhaus::getMinLength() / 2.0f;

	Einfamilienhaus * b = new Einfamilienhaus(m_center, front, side);
	addBuilding2(* b);

}