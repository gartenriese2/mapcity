#include "Building.hpp"

Building::Building() {
	// std::cout << "Building created\n";
}

Building::~Building() {
	deleteObject();
}

void Building::createObject() {
	// std::cout << "creating Object ...\n";
	m_ID = ObjectContainer::instance().addBuilding(m_center, m_front, m_side, m_height, m_color);
}

void Building::deleteObject() {
	ObjectContainer::instance().deleteBuilding(m_ID);
}