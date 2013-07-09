#include "ObjectContainer.hpp"

static unsigned long count = 1;

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

unsigned long ObjectContainer::addBuilding(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side, const float height, const glm::vec3 & color) {

	std::lock_guard<std::mutex> guard(sMutex);

	BuildingData d;
	d.ID = count++;
	d.center = center;
	d.front = front;
	d.side = side;
	d.height = height;
	d.color = color;
	m_buildingQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::emptyBuildingQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_buildingQueue.empty()) {

		BuildingData d = m_buildingQueue.front();
		Object o(ObjectType::CUBOID, d.center, d.front, d.side, d.height, d.color);
		m_buildingMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_buildingQueue.pop();

	}

}

unsigned long ObjectContainer::addZone(const vectorVec3 & pts, const glm::vec3 & center, const glm::vec3 & color) {
	
	std::lock_guard<std::mutex> guard(sMutex);

	ZoneData d;
	d.ID = count++;
	d.pts = pts;
	d.center = center;
	d.color = color;
	m_zoneQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::emptyZoneQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_zoneQueue.empty()) {

		ZoneData d = m_zoneQueue.front();
		Object o(ObjectType::POLYGON, d.pts, d.center, d.color);
		m_zoneMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_zoneQueue.pop();

	}

}

unsigned long ObjectContainer::addHexagon(const glm::vec3 & center, const glm::vec3 & left, const glm::vec3 & color) {
	
	std::lock_guard<std::mutex> guard(sMutex);

	HexagonData d;
	d.ID = count++;
	d.center = center;
	d.left = left;
	d.color = color;
	m_hexagonQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::emptyHexagonQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_hexagonQueue.empty()) {

		HexagonData d = m_hexagonQueue.front();
		Object o(ObjectType::HEXAGON, d.center, d.left, d.color);
		m_hexagonMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_hexagonQueue.pop();

	}

}

unsigned long ObjectContainer::addPath(const vectorVec3 & pts, const float width, const glm::vec3 & color) {
	
	std::lock_guard<std::mutex> guard(sMutex);

	PathData d;
	d.ID = count++;
	d.pts = pts;
	d.width = width;
	d.color = color;
	m_pathQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::emptyPathQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_pathQueue.empty()) {

		PathData d = m_pathQueue.front();
		Object o(ObjectType::SPLINE, d.pts, d.width, d.color);
		m_pathMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_pathQueue.pop();

	}

}