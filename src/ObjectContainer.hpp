#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "SplineObject.hpp"
#include "CuboidObject.hpp"
#include "PolygonObject.hpp"
#include "HexagonObject.hpp"

#include <unordered_map>
#include <memory>
#include <mutex>
#include <queue>

typedef std::unordered_map<unsigned long, SplineObject> pathMap;
typedef std::unordered_map<unsigned long, CuboidObject> cuboidMap;
typedef std::unordered_map<unsigned long, PolygonObject> zoneMap;
typedef std::unordered_map<unsigned long, HexagonObject> hexagonMap;

class ObjectContainer {
	public:
		
		static ObjectContainer& instance();

		unsigned long addCuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 &);
		void changeCuboidHeight(const unsigned long, const float);
		void emptyCuboidQueue();
		void deleteCuboid(const unsigned long);
		void moveCuboid(const unsigned long, const glm::vec3 &);
		void rotateCuboid(const unsigned long, const float);
		const cuboidMap & getCuboids() const;

		unsigned long addZone(const vectorVec3 &, const glm::vec3 &, const glm::vec3 &);
		void emptyZoneQueue();
		void deleteZone(const unsigned long ID);
		const zoneMap & getZones() const;

		unsigned long addHexagon(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		void emptyHexagonQueue();
		void deleteHexagon(const unsigned long ID);
		const hexagonMap & getHexagons() const;

		unsigned long addPath(const vectorVec3 &, const float, const glm::vec3 &);
		void emptyPathQueue();
		void deletePath(const unsigned long ID);
		const pathMap & getPaths() const;

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
		
		cuboidMap m_cuboidMap;
		zoneMap m_zoneMap;
		hexagonMap m_hexagonMap;
		pathMap m_pathMap;

		struct CuboidData {
			unsigned long ID;
			glm::vec3 center;
			glm::vec3 front;
			glm::vec3 side;
			float height;
			glm::vec3 color;
		};
		std::queue<CuboidData> m_cuboidAddQueue;
		std::queue<unsigned long> m_cuboidDeleteQueue;
		std::queue<CuboidData> m_cuboidChangeQueue;

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