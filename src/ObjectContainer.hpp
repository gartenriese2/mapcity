#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "Object.hpp"
#include <unordered_map>
#include <memory>
#include <mutex>

typedef std::unordered_map<unsigned long, Object> objectMap;

class ObjectContainer {
	public:
		
		static ObjectContainer& instance();

		unsigned long addBuilding(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 &);
		void deleteBuilding(const unsigned long ID) { mBuildingMap.erase(ID); }
		const objectMap & getBuildings() const { return mBuildingMap; }

		unsigned long addZone(const vectorVec3 &, const glm::vec3 &, const glm::vec3 &);
		void deleteZone(const unsigned long ID) { mZoneMap.erase(ID); }
		const objectMap & getZones() const { return mZoneMap; }

		unsigned long addHexagon(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		void deleteHexagon(const unsigned long ID) { mHexagonMap.erase(ID); }
		const objectMap & getHexagons() const { return mHexagonMap; }

		unsigned long addPath(const vectorVec3 &, const float, const glm::vec3 &);
		void deletePath(const unsigned long ID) { mPathMap.erase(ID); }
		const objectMap & getPaths() const { return mPathMap; }

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
		
		objectMap mBuildingMap;
		objectMap mZoneMap;
		objectMap mHexagonMap;
		objectMap mPathMap;

};

#endif