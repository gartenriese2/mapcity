#ifndef MIETSHAUS_HPP
#define MIETSHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Mietshaus : public ResidentialBuilding {
	
	const unsigned short k_minFloors = 3;
	const unsigned short k_maxFloors = 8;
	unsigned short k_numHouseholds = 10;

	public:
		Mietshaus(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~Mietshaus();
	
};

class MietshausZone : public ResidentialZone {
	public:
		MietshausZone(const vectorVec3 &);
		virtual ~MietshausZone();
		
};

#endif