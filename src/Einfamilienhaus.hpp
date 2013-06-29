#ifndef EINFAMILIENHAUS_HPP
#define EINFAMILIENHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Einfamilienhaus : public ResidentialBuilding {
	
	const float k_minHeight = 4.0;
	const float k_maxHeight = 10.0;
	const int k_numHouseholds = 1;

	public:
		Einfamilienhaus(glm::vec3, glm::vec3, glm::vec3);
		~Einfamilienhaus();
	
};

class EinfamilienhausZone : public ResidentialZone {
	public:
		EinfamilienhausZone(std::vector<glm::vec3>);
		~EinfamilienhausZone();
		

		
	private:
		void addBuilding() {
			
		}
		
};

#endif