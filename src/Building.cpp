#include "Building.hpp"

Building::Building() {
	
	m_constructionStart = Time::instance().getIngameTime();

}

Building::~Building() {
	deleteObject();
}

void Building::setHeight(const float minFloorHeight, const float maxFloorHeight, int minFloors, int maxFloors) {
	
	m_floors = glm::round(glm::linearRand(static_cast<float>(minFloors), static_cast<float>(maxFloors)));
	m_height = glm::linearRand(minFloorHeight, maxFloorHeight) * m_floors;

}

void Building::createObject() {
	m_ID = ObjectContainer::instance().addCuboid(m_center, m_front, m_side, m_actualHeight, m_color);
}

void Building::deleteObject() {
	ObjectContainer::instance().deleteCuboid(m_ID);
}

void Building::changeObjectHeight() {
	ObjectContainer::instance().changeCuboidHeight(m_ID, m_actualHeight);
}

void Building::construct() {

	if (m_actualHeight < m_height) {
		
		m_actualHeight = Time::instance().getSecondsSinceTimePoint(m_constructionStart) * (k_constructionHeightPerDay / (24.f * 3600.f));
		
		if (m_actualHeight > m_height) {
			m_actualHeight = m_height;
			m_constructionDone = true;
		}

		changeObjectHeight();
		
	}

}