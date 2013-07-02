#ifndef EINFAMILIENHAUS_HPP
#define EINFAMILIENHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Einfamilienhaus : public ResidentialBuilding {
	
	const float k_minHeight = 4.0;
	const float k_maxHeight = 10.0;
	const int k_numHouseholds = 1;

	public:
		Einfamilienhaus(const glm::vec3, const glm::vec3, const glm::vec3);
		virtual ~Einfamilienhaus();
	
};

class EinfamilienhausZone : public ResidentialZone {
	public:
		EinfamilienhausZone(const vectorVec3);
		virtual ~EinfamilienhausZone();
		
};

#endif