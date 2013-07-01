#include "Building.hpp"

Building::Building() {
	
}

Building::~Building() {
	deleteObject();
}

void Building::createObject() {
	m_ID = ObjectContainer::instance().addBuilding(m_center, m_front, m_side, m_height, m_color);
}

void Building::deleteObject() {
	ObjectContainer::instance().deleteBuilding(m_ID);
}