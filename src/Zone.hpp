#ifndef ZONE_HPP
#define ZONE_HPP

#include "../glm-0.9.4.3/glm/glm.hpp"
#include <vector>
#include <iostream>
#include "Building.hpp"

// template <class T> class Zone {
class Zone {
	
	static int count;

	public:
		Zone();
		~Zone();

		// Getter
		inline std::vector<glm::vec3> getBounding() { return this->bounding; }
		inline int getID() { return this->ID; }
		inline float getArea() { return this->area; }
		inline glm::vec3 getCenter() { return this->center; }

		// Setter
		
		inline std::vector<Building*> getBuildings() { return buildings; }
		
		// inline void addBuilding(Building b) { buildings.push_back(b); }
		void deleteBuilding(Building b);

		bool isDeveloped() { return buildings.size() != 0; }
		// inline void addBuilding(T b) { buildings.push_back(b); }

		std::vector<Building*> buildings;

		virtual void addBuilding() {}

	private:
		std::vector<glm::vec3> bounding;
		float area;
		glm::vec3 center;
		int ID;
		
		

		

	protected:
		
		

		void setArea();
		void setCenter();
		void setBounding(std::vector<glm::vec3> b) { bounding = b; }

};

#endif