#ifndef EINFAMILIENHAUS_HPP
#define EINFAMILIENHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Einfamilienhaus : public ResidentialBuilding {
	
	const unsigned short k_minFloors = 1;
	const unsigned short k_maxFloors = 3;
	const unsigned short k_numHouseholds = 1;

	public:
		Einfamilienhaus(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~Einfamilienhaus();
	
};

class EinfamilienhausZone : public ResidentialZone {
	
	public:
		
		EinfamilienhausZone(const vectorVec3 &);
		virtual ~EinfamilienhausZone();

		void addBuilding();
		
};

#endif