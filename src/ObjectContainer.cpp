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
	m_buildingAddQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::deleteBuilding(const unsigned long ID) { 
	
	std::lock_guard<std::mutex> guard(sMutex);

	m_buildingDeleteQueue.push(ID);

}

const objectMap & ObjectContainer::getBuildings() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_buildingMap;

}

void ObjectContainer::emptyBuildingQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_buildingAddQueue.empty()) {

		BuildingData d = m_buildingAddQueue.front();
		Object o(ObjectType::CUBOID, d.center, d.front, d.side, d.height, d.color);
		m_buildingMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_buildingAddQueue.pop();

	}

	while(!m_buildingDeleteQueue.empty()) {

		unsigned long ID = m_buildingDeleteQueue.front();
		m_buildingMap.erase(ID);
		m_buildingDeleteQueue.pop();

	}

}

unsigned long ObjectContainer::addZone(const vectorVec3 & pts, const glm::vec3 & center, const glm::vec3 & color) {
	
	std::lock_guard<std::mutex> guard(sMutex);

	ZoneData d;
	d.ID = count++;
	d.pts = pts;
	d.center = center;
	d.color = color;
	m_zoneAddQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::deleteZone(const unsigned long ID) { 
	
	std::lock_guard<std::mutex> guard(sMutex);

	m_zoneDeleteQueue.push(ID);

}

const objectMap & ObjectContainer::getZones() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_zoneMap;

}

void ObjectContainer::emptyZoneQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_zoneAddQueue.empty()) {

		ZoneData d = m_zoneAddQueue.front();
		Object o(ObjectType::POLYGON, d.pts, d.center, d.color);
		m_zoneMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_zoneAddQueue.pop();

	}

	while(!m_zoneDeleteQueue.empty()) {

		unsigned long ID = m_zoneDeleteQueue.front();
		m_zoneMap.erase(ID);
		m_zoneDeleteQueue.pop();

	}

}

unsigned long ObjectContainer::addHexagon(const glm::vec3 & center, const glm::vec3 & left, const glm::vec3 & color) {
	
	std::lock_guard<std::mutex> guard(sMutex);

	HexagonData d;
	d.ID = count++;
	d.center = center;
	d.left = left;
	d.color = color;
	m_hexagonAddQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::deleteHexagon(const unsigned long ID) { 
	
	std::lock_guard<std::mutex> guard(sMutex);

	m_hexagonDeleteQueue.push(ID);

}

const objectMap & ObjectContainer::getHexagons() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_hexagonMap;

}

void ObjectContainer::emptyHexagonQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_hexagonAddQueue.empty()) {

		HexagonData d = m_hexagonAddQueue.front();
		Object o(ObjectType::HEXAGON, d.center, d.left, d.color);
		m_hexagonMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_hexagonAddQueue.pop();

	}

	while(!m_hexagonDeleteQueue.empty()) {

		unsigned long ID = m_hexagonDeleteQueue.front();
		m_hexagonMap.erase(ID);
		m_hexagonDeleteQueue.pop();

	}

}

unsigned long ObjectContainer::addPath(const vectorVec3 & pts, const float width, const glm::vec3 & color) {
	
	std::lock_guard<std::mutex> guard(sMutex);

	PathData d;
	d.ID = count++;
	d.pts = pts;
	d.width = width;
	d.color = color;
	m_pathAddQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::deletePath(const unsigned long ID) { 
	
	std::lock_guard<std::mutex> guard(sMutex);

	m_pathDeleteQueue.push(ID);

}

const objectMap & ObjectContainer::getPaths() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_pathMap;

}

void ObjectContainer::emptyPathQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_pathAddQueue.empty()) {

		PathData d = m_pathAddQueue.front();
		Object o(ObjectType::SPLINE, d.pts, d.width, d.color);
		m_pathMap.insert(std::pair<unsigned long,Object>(d.ID, o));
		m_pathAddQueue.pop();

	}

	while(!m_pathDeleteQueue.empty()) {

		unsigned long ID = m_pathDeleteQueue.front();
		m_pathMap.erase(ID);
		m_pathDeleteQueue.pop();

	}

}