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
		void deleteBuilding(const unsigned long ID);
		const objectMap & getBuildings() const;

		unsigned long addZone(const vectorVec3 &, const glm::vec3 &, const glm::vec3 &);
		void emptyZoneQueue();
		void deleteZone(const unsigned long ID);
		const objectMap & getZones() const;

		unsigned long addHexagon(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		void emptyHexagonQueue();
		void deleteHexagon(const unsigned long ID);
		const objectMap & getHexagons() const;

		unsigned long addPath(const vectorVec3 &, const float, const glm::vec3 &);
		void emptyPathQueue();
		void deletePath(const unsigned long ID);
		const objectMap & getPaths() const;

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
		std::queue<BuildingData> m_buildingAddQueue;
		std::queue<unsigned long> m_buildingDeleteQueue;

		struct HexagonData {
			unsigned long ID;
			glm::vec3 center;
			glm::vec3 left;
			glm::vec3 color;
		};
		std::queue<HexagonData> m_hexagonAddQueue;
		std::queue<unsigned long> m_hexagonDeleteQueue;

		struct ZoneData {
			unsigned long ID;
			vectorVec3 pts;
			glm::vec3 center;
			glm::vec3 color;
		};
		std::queue<ZoneData> m_zoneAddQueue;
		std::queue<unsigned long> m_zoneDeleteQueue;

		struct PathData {
			unsigned long ID;
			vectorVec3 pts;
			float width;
			glm::vec3 color;
		};
		std::queue<PathData> m_pathAddQueue;
		std::queue<unsigned long> m_pathDeleteQueue;

};

#endif