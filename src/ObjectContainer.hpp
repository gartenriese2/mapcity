#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "Object.hpp"
#include <unordered_map>
#include <memory>

class ObjectContainer {
public:
	
	static ObjectContainer& instance();

	unsigned long addBuilding(const glm::vec3, const glm::vec3, const glm::vec3, const float, const glm::vec3);
	void deleteBuilding(const unsigned long ID) { mBuildingMap.erase(ID); }
	std::unordered_map<unsigned long, Object> getBuildings() const { return mBuildingMap; }

	unsigned long addHexagon(const glm::vec3, const glm::vec3, const glm::vec3);
	void deleteHexagon(const unsigned long ID) { mHexagonMap.erase(ID); }

protected:

private:
	
	ObjectContainer();
	virtual ~ObjectContainer();
	
	std::unordered_map<unsigned long, Object> mBuildingMap;
	std::unordered_map<unsigned long, Object> mZoneMap;
	std::unordered_map<unsigned long, Object> mHexagonMap;

};

#endif