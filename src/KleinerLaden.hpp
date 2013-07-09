#ifndef KLEINERLADEN_HPP
#define KLEINERLADEN_HPP

#include "BusinessBuilding.hpp"
#include "BusinessZone.hpp"

class KleinerLaden : public BusinessBuilding {
	
	const unsigned short k_minFloors = 1;
	const unsigned short k_maxFloors = 2;

	public:
		KleinerLaden(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~KleinerLaden();
	
};

class KleinerLadenZone : public BusinessZone {
	public:
		KleinerLadenZone(const vectorVec3 &);
		virtual ~KleinerLadenZone();
		
};

#endif