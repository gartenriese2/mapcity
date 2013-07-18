#include "Building.hpp"

Building::Building() {
	m_constructionStart = Time::instance().getIngameTime();
	m_actualHeight = 0.01f;
	m_constructionDone = false;
}

Building::~Building() {
	deleteObject();
}

void Building::setHeight(const float minFloorHeight, const float maxFloorHeight, int minFloors, int maxFloors) {
	 m_height = glm::linearRand(minFloorHeight, maxFloorHeight)
	 			* glm::round(glm::linearRand(static_cast<float>(minFloors), static_cast<float>(maxFloors)));
}

void Building::createObject() {
	m_ID = ObjectContainer::instance().addBuilding(m_center, m_front, m_side, m_actualHeight, m_color);
}

void Building::deleteObject() {
	ObjectContainer::instance().deleteBuilding(m_ID);
}

void Building::changeObjectHeight() {
	ObjectContainer::instance().changeBuildingHeight(m_ID, m_actualHeight);
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