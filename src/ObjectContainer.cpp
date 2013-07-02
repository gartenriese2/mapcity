#include "ObjectContainer.hpp"

ObjectContainer* ObjectContainer::pInstance = nullptr;
std::mutex ObjectContainer::sMutex;

ObjectContainer& ObjectContainer::instance() {
	
	static Cleanup cleanup;
	std::lock_guard<std::mutex> guard(sMutex);
	if (pInstance == nullptr) {
		pInstance = new ObjectContainer();
	}
	
	return *pInstance;
}

ObjectContainer::Cleanup::~Cleanup() {
	std::lock_guard<std::mutex> gaurd(ObjectContainer::sMutex);
	delete ObjectContainer::pInstance;
	ObjectContainer::pInstance = nullptr;
}

ObjectContainer::ObjectContainer() {
	
}

ObjectContainer::~ObjectContainer() {

}

unsigned long ObjectContainer::addBuilding(const glm::vec3 center, const glm::vec3 dirX, const glm::vec3 dirZ, const float height, const glm::vec3 color) {

	std::lock_guard<std::mutex> guard(sMutex);

	Object o(ObjectType::CUBOID, center, dirX, dirZ, height, color);
	unsigned long ID = o.getID();
	mBuildingMap.insert(std::pair<unsigned long,Object>(ID, o));
	
	return ID;

}

unsigned long ObjectContainer::addZone(const vectorVec3 pts, const glm::vec3 center, const glm::vec3 color) {

	std::lock_guard<std::mutex> guard(sMutex);

	Object o(ObjectType::POLYGON, pts, center, color);
	unsigned long ID = o.getID();
	mZoneMap.insert(std::pair<unsigned long,Object>(ID, o));
	
	return ID;

}

unsigned long ObjectContainer::addHexagon(const glm::vec3 center, const glm::vec3 left, const glm::vec3 color) {

	std::lock_guard<std::mutex> guard(sMutex);

	Object o(ObjectType::HEXAGON, center, left, color);
	unsigned long ID = o.getID();
	mHexagonMap.insert(std::pair<unsigned long,Object>(ID, o));
	return ID;

}

unsigned long ObjectContainer::addPath(const vectorVec3 pts, const float width, const glm::vec3 color) {

	std::lock_guard<std::mutex> guard(sMutex);

	Object o(ObjectType::SPLINE, pts, width, color);
	unsigned long ID = o.getID();
	mPathMap.insert(std::pair<unsigned long, Object>(ID, o));
	return ID;

}