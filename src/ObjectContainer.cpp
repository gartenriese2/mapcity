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

unsigned long ObjectContainer::addCuboid(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side, const float height, const glm::vec3 & color) {

	std::lock_guard<std::mutex> guard(sMutex);

	CuboidData d;
	d.ID = count++;
	d.center = center;
	d.front = front;
	d.side = side;
	d.height = height;
	d.color = color;
	m_cuboidAddQueue.push(d);
	
	return d.ID;

}

void ObjectContainer::changeCuboidHeight(const unsigned long ID, const float height) {

	std::lock_guard<std::mutex> guard(sMutex);

	CuboidData d;
	d.ID = ID;
	d.height = height;
	m_cuboidChangeQueue.push(d);

}

void ObjectContainer::deleteCuboid(const unsigned long ID) { 
	
	std::lock_guard<std::mutex> guard(sMutex);

	m_cuboidDeleteQueue.push(ID);

}

void ObjectContainer::moveCuboid(const unsigned long ID, const glm::vec3 & mov) {

	std::lock_guard<std::mutex> guard(sMutex);

	m_cuboidMap.at(ID).move(mov);

}

const cuboidMap & ObjectContainer::getCuboids() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_cuboidMap;

}

void ObjectContainer::emptyCuboidQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_cuboidAddQueue.empty()) {

		CuboidData d = m_cuboidAddQueue.front();
		//CuboidObject o(d.center, d.front, d.side, d.height, d.color);
		// std::cout << __LINE__ << "\n";
		m_cuboidMap.insert(std::pair<unsigned long,CuboidObject>(d.ID, CuboidObject(d.center, d.front, d.side, d.height, d.color)));
		// std::cout << __LINE__ << "\n";
		m_cuboidAddQueue.pop();

	}

	while(!m_cuboidDeleteQueue.empty()) {

		unsigned long ID = m_cuboidDeleteQueue.front();
		m_cuboidMap.erase(ID);
		m_cuboidDeleteQueue.pop();

	}

	while(!m_cuboidChangeQueue.empty()) {

		CuboidData d = m_cuboidChangeQueue.front();
		m_cuboidMap.at(d.ID).changeHeight(d.height);
		m_cuboidChangeQueue.pop();

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

const zoneMap & ObjectContainer::getZones() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_zoneMap;

}

void ObjectContainer::emptyZoneQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_zoneAddQueue.empty()) {

		ZoneData d = m_zoneAddQueue.front();
		//PolygonObject o(d.pts, d.center, d.color);
		// std::cout << __LINE__ << "\n";
		m_zoneMap.insert(std::pair<unsigned long,PolygonObject>(d.ID, PolygonObject(d.pts, d.center, d.color)));
		// std::cout << __LINE__ << "\n";
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

const hexagonMap & ObjectContainer::getHexagons() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_hexagonMap;

}

void ObjectContainer::emptyHexagonQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_hexagonAddQueue.empty()) {

		HexagonData d = m_hexagonAddQueue.front();
		// HexagonObject o(d.center, d.left, d.color);
		// std::cout << __LINE__ << "\n";
		m_hexagonMap.insert(std::pair<unsigned long,HexagonObject>(d.ID, HexagonObject(d.center, d.left, d.color)));
		// std::cout << __LINE__ << "\n";
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

const pathMap & ObjectContainer::getPaths() const { 

	std::lock_guard<std::mutex> guard(sMutex);

	return m_pathMap;

}

void ObjectContainer::emptyPathQueue() {

	std::lock_guard<std::mutex> guard(sMutex);

	while(!m_pathAddQueue.empty()) {

		PathData d = m_pathAddQueue.front();
		// SplineObject o(d.pts, d.width, d.color);
		// std::cout << __LINE__ << "\n";
		m_pathMap.insert(std::pair<unsigned long,SplineObject>(d.ID, SplineObject(d.pts, d.width, d.color)));
		// std::cout << __LINE__ << "\n";
		m_pathAddQueue.pop();

	}

	while(!m_pathDeleteQueue.empty()) {

		unsigned long ID = m_pathDeleteQueue.front();
		m_pathMap.erase(ID);
		m_pathDeleteQueue.pop();

	}

}