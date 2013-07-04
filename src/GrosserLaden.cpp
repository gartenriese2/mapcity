#include "GrosserLaden.hpp"

GrosserLaden::GrosserLaden(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side) {

	setShape(center, front, side);
	setHeight(k_minHeight, k_maxHeight);
	
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