#ifndef MIETSHAUS_HPP
#define MIETSHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Mietshaus : public ResidentialBuilding {
	
	const float k_minHeight = 20.0;
	const float k_maxHeight = 40.0;
	const int floors = 1;
	const int k_numHouseholds = 1;

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