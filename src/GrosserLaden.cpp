#include "GrosserLaden.hpp"

GrosserLaden::GrosserLaden(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side) {

	setShape(center, front, side);
	setHeight(k_minFloorHeight, k_maxFloorHeight, k_minFloors, k_maxFloors);
	
	createObject();

}

GrosserLaden::~GrosserLaden() {
	
}

GrosserLadenZone::GrosserLadenZone(const vectorVec3 & bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

GrosserLadenZone::~GrosserLadenZone() {
	
}

void GrosserLadenZone::addBuilding() {

	// calculate center & shape for new building
	// create building and add it to vector

	GrosserLaden * b = new GrosserLaden(m_center, glm::vec3(1,0,0), glm::vec3(0,0,-1));
	addBuilding2(* b);

}