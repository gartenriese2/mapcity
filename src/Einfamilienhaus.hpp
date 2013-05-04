#ifndef EINFAMILIENHAUS_HPP
#define EINFAMILIENHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Einfamilienhaus : public ResidentialBuilding {
	public:
		Einfamilienhaus(glm::vec3, glm::vec3, float, float, float);
		~Einfamilienhaus();
	private:

		
};

class EinfamilienhausZone : public ResidentialZone {
	public:
		EinfamilienhausZone(std::vector<glm::vec3>);
		~EinfamilienhausZone();
		

		
	private:
		void addBuilding() {
			buildings.push_back(new Einfamilienhaus(glm::vec3(1,0,0),glm::vec3(1,0,0),1,1,1));
		}
		
};

#endif