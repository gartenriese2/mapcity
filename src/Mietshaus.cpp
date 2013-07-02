#include "Mietshaus.hpp"

Mietshaus::Mietshaus(glm::vec3 center, glm::vec3 front, glm::vec3 side) {

	setShape(center, front, side);
	setHeight(k_minHeight, k_maxHeight);
	
	createObject();
	createHouseholds(k_numHouseholds);

}

Mietshaus::~Mietshaus() {
	
}

MietshausZone::MietshausZone(vectorVec3 bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

MietshausZone::~MietshausZone() {
	
}