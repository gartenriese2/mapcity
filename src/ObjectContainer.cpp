#include "ObjectContainer.hpp"

ObjectContainer& ObjectContainer::instance() {
	static ObjectContainer sInstance;
	return sInstance;
}

ObjectContainer::ObjectContainer() {
	
}

ObjectContainer::~ObjectContainer() {

}

unsigned long ObjectContainer::addBuilding(const glm::vec3 center, const glm::vec3 dirX, const glm::vec3 dirZ, const float height, const glm::vec3 color) {

	Object o(ObjectType::CUBOID, center, dirX, dirZ, height, color);
	unsigned long ID = o.getID();
	mBuildingMap.insert(std::pair<unsigned long,Object>(ID, o));
	return ID;

}

unsigned long ObjectContainer::addHexagon(const glm::vec3 center, const glm::vec3 left, const glm::vec3 color) {

	Object o(ObjectType::HEXAGON, center, left, color);
	unsigned long ID = o.getID();
	mHexagonMap.insert(std::pair<unsigned long,Object>(ID, o));
	return ID;

}