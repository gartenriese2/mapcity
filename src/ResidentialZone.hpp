#ifndef RESIDENTIALZONE_HPP
#define RESIDENTIALZONE_HPP

#include "Zone.hpp"

class ResidentialZone : public Zone {
	
	const glm::vec3 k_color = glm::vec3(0.6, 1.0, 0.6);

	public:
		ResidentialZone();
		virtual ~ResidentialZone();

		virtual bool isResidential() const { return true; }
		virtual int getResidents() const { return 10; }
		
};

#endif