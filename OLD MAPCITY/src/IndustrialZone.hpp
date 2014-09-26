#ifndef INDUSTRIALZONE_HPP
#define INDUSTRIALZONE_HPP

#include "Zone.hpp"

class IndustrialZone : public Zone {

	const glm::vec3 k_color = glm::vec3(1.0, 1.0, 0.6);

	public:
		IndustrialZone();
		virtual ~IndustrialZone();
		
		virtual bool isIndustrial() const { return true; }
		
};

#endif