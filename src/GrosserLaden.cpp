#include "GrosserLaden.hpp"

GrosserLaden::GrosserLaden(glm::vec3 center, glm::vec3 front, glm::vec3 side) {

	setShape(center, front, side);
	setHeight(k_minHeight, k_maxHeight);
	
	createObject();

}

GrosserLaden::~GrosserLaden() {
	
}

GrosserLadenZone::GrosserLadenZone(vectorVec3 bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

	createObject();

}

GrosserLadenZone::~GrosserLadenZone() {
	
}