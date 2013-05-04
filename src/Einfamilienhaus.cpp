#include "Einfamilienhaus.hpp"

Einfamilienhaus::Einfamilienhaus(glm::vec3 center, glm::vec3 align, float height, float width, float length) {

	createOutline();
	createHouseholds(1);
	setCenter(center);
	setAlignment(align);
	setSize(height, width, length);

}

Einfamilienhaus::~Einfamilienhaus() {
	
}

EinfamilienhausZone::EinfamilienhausZone(std::vector<glm::vec3> bounding) {

	setBounding(bounding);
	setArea();
	setCenter();

}

EinfamilienhausZone::~EinfamilienhausZone() {
	
}