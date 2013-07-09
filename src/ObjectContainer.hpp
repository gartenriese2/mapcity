#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "Object.hpp"
#include <unordered_map>
#include <memory>
#include <mutex>
#include <queue>

typedef std::unordered_map<unsigned long, Object> objectMap;

class ObjectContainer {
	public:
		
		static ObjectContainer& instance();

		unsigned long addBuilding(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 &);
		void emptyBuildingQueue();
		void deleteBuilding(const unsigned long ID) { m_buildingMap.erase(ID); }
		const objectMap & getBuildings() const { return m_buildingMap; }

		unsigned long addZone(const vectorVec3 &, const glm::vec3 &, const glm::vec3 &);
		void emptyZoneQueue();
		void deleteZone(const unsigned long ID) { m_zoneMap.erase(ID); }
		const objectMap & getZones() const { return m_zoneMap; }

		unsigned long addHexagon(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		void emptyHexagonQueue();
		void deleteHexagon(const unsigned long ID) { m_hexagonMap.erase(ID); }
		const objectMap & getHexagons() const { return m_hexagonMap; }

		unsigned long addPath(const vectorVec3 &, const float, const glm::vec3 &);
		void emptyPathQueue();
		void deletePath(const unsigned long ID) { m_pathMap.erase(ID); }
		const objectMap & getPaths() const { return m_pathMap; }

	protected:
		
		static ObjectContainer* pInstance;

		friend class Cleanup;
		class Cleanup {
			public:
				~Cleanup();
		};
		
	private:

		ObjectContainer();
		virtual ~ObjectContainer();
		ObjectContainer(const ObjectContainer&);
		ObjectContainer& operator=(const ObjectContainer&);
		static std::mutex sMutex;
		
		objectMap m_buildingMap;
		objectMap m_zoneMap;
		objectMap m_hexagonMap;
		objectMap m_pathMap;

		struct BuildingData {
			unsigned long ID;
			glm::vec3 center;
			glm::vec3 front;
			glm::vec3 side;
			float height;
			glm::vec3 color;
		};
		std::queue<BuildingData> m_buildingQueue;

		struct HexagonData {
			unsigned long ID;
			glm::vec3 center;
			glm::vec3 left;
			glm::vec3 color;
		};
		std::queue<HexagonData> m_hexagonQueue;

		struct ZoneData {
			unsigned long ID;
			vectorVec3 pts;
			glm::vec3 center;
			glm::vec3 color;
		};
		std::queue<ZoneData> m_zoneQueue;

		struct PathData {
			unsigned long ID;
			vectorVec3 pts;
			float width;
			glm::vec3 color;
		};
		std::queue<PathData> m_pathQueue;

};

#endif