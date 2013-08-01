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

	float angle = glm::linearRand(0.0, 3.14);
	glm::vec3 sideDir = -glm::normalize(glm::vec3(-glm::sin(angle + 0.78),0,glm::cos(angle)));
	glm::vec3 frontDir = glm::normalize(glm::vec3(glm::cos(angle),0,glm::sin(angle + 0.78)));
	
	glm::vec3 side = sideDir * KleinerLaden::getMinWidth() / 2.0f;
	glm::vec3 front = frontDir * KleinerLaden::getMinLength() / 2.0f;

	KleinerLaden * b = new KleinerLaden(m_center, front, side);
	addBuilding2(* b);

}