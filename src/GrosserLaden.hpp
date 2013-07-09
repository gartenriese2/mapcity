#ifndef GROSSERLADEN_HPP
#define GROSSERLADEN_HPP

#include "BusinessBuilding.hpp"
#include "BusinessZone.hpp"

class GrosserLaden : public BusinessBuilding {
	
	const unsigned short k_minFloors = 1;
	const unsigned short k_maxFloors = 2;

	public:
		GrosserLaden(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~GrosserLaden();
	
};

class GrosserLadenZone : public BusinessZone {
	public:
		GrosserLadenZone(const vectorVec3 &);
		virtual ~GrosserLadenZone();
		
};

#endif