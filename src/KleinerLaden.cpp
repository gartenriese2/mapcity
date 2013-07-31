#include "KleinerLaden.hpp"

KleinerLaden::KleinerLaden(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side) {

	setShape(center, front, side);
	setHeight(k_minFloorHeight, k_maxFloorHeight, k_minFloors, k_maxFloors);
	
	createObject();

}

KleinerLaden::~KleinerLaden() {
	
}

KleinerLadenZone::KleinerLadenZone(const vectorVec3 & bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

KleinerLadenZone::~KleinerLadenZone() {
	
}

void KleinerLadenZone::addBuilding() {

	// calculate center & shape for new building
	// create building and add it to vector

	glm::vec3 sideDir = glm::vec3(0,0,-1);
	glm::vec3 frontDir = glm::vec3(1,0,0);
	glm::vec3 side = sideDir * KleinerLaden::getMinWidth() / 2.0f;
	glm::vec3 front = frontDir * KleinerLaden::getMinLength() / 2.0f;

	KleinerLaden * b = new KleinerLaden(m_center, front, side);
	addBuilding2(* b);

}