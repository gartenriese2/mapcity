#ifndef BUSINESSZONE_HPP
#define BUSINESSZONE_HPP

#include "Zone.hpp"

class BusinessZone : public Zone {
	
	const glm::vec3 k_color = glm::vec3(0.6, 0.6, 1.0);

	public:
		BusinessZone();
		virtual ~BusinessZone();
		
};

#endif