#include "KleinerLaden.hpp"

KleinerLaden::KleinerLaden(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side) {

	setShape(center, front, side);
	setHeight(k_minHeight, k_maxHeight);
	
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