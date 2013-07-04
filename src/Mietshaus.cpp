#include "Mietshaus.hpp"

Mietshaus::Mietshaus(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side) {

	setShape(center, front, side);
	setHeight(k_minHeight, k_maxHeight);
	
	createObject();
	createHouseholds(k_numHouseholds);

}

Mietshaus::~Mietshaus() {
	
}

MietshausZone::MietshausZone(const vectorVec3 & bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

MietshausZone::~MietshausZone() {
	
}