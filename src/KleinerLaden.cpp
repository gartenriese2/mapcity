#include "KleinerLaden.hpp"

KleinerLaden::KleinerLaden(glm::vec3 center, glm::vec3 front, glm::vec3 side) {

	setShape(center, front, side);
	setHeight(k_minHeight, k_maxHeight);
	
	createObject();

}

KleinerLaden::~KleinerLaden() {
	
}

KleinerLadenZone::KleinerLadenZone(vectorVec3 bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

KleinerLadenZone::~KleinerLadenZone() {
	
}