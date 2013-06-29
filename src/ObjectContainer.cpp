#include "ObjectContainer.hpp"

ObjectContainer* ObjectContainer::pInstance = nullptr;
std::mutex ObjectContainer::sMutex;

ObjectContainer& ObjectContainer::instance() {
	// std::cout << "getting instance ...\n";
	static Cleanup cleanup;
	std::lock_guard<std::mutex> guard(sMutex);
	if (pInstance == nullptr) {
		// std::cout << "is nullptr\n";
		pInstance = new ObjectContainer();
	}
	// std::cout << "got instance ...\n";
	return *pInstance;
}

ObjectContainer::Cleanup::~Cleanup() {
	std::lock_guard<std::mutex> gaurd(ObjectContainer::sMutex);
	delete ObjectContainer::pInstance;
	ObjectContainer::pInstance = nullptr;
}

ObjectContainer::ObjectContainer() {
	// std::cout << "creating ObjectContainer ...\n";
}

ObjectContainer::~ObjectContainer() {

}

unsigned long ObjectContainer::addBuilding(const glm::vec3 center, const glm::vec3 dirX, const glm::vec3 dirZ, const float height, const glm::vec3 color) {

	// std::cout << "adding Building ...\n";

	std::lock_guard<std::mutex> guard(sMutex);

	// std::cout << "locked!\n";

	Object o(ObjectType::CUBOID, center, dirX, dirZ, height, color);
	// std::cout << "created Object.\n";
	unsigned long ID = o.getID();
	mBuildingMap.insert(std::pair<unsigned long,Object>(ID, o));
	std::cout << "added Building ...\n";
	return ID;

}

unsigned long ObjectContainer::addHexagon(const glm::vec3 center, const glm::vec3 left, const glm::vec3 color) {

	std::lock_guard<std::mutex> guard(sMutex);

	Object o(ObjectType::HEXAGON, center, left, color);
	unsigned long ID = o.getID();
	mHexagonMap.insert(std::pair<unsigned long,Object>(ID, o));
	return ID;

}