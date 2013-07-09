#include "Building.hpp"

Building::Building() {
	
}

Building::~Building() {
	deleteObject();
}

void Building::setHeight(const float minFloorHeight, const float maxFloorHeight, int minFloors, int maxFloors) {
	 m_height = glm::linearRand(minFloorHeight, maxFloorHeight)
	 			* glm::round(glm::linearRand(static_cast<float>(minFloors), static_cast<float>(maxFloors)));
}

void Building::createObject() {
	m_ID = ObjectContainer::instance().addBuilding(m_center, m_front, m_side, m_height, m_color);
}

void Building::deleteObject() {
	ObjectContainer::instance().deleteBuilding(m_ID);
}