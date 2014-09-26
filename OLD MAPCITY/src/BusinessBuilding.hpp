#ifndef BUSINESSBUILDING_HPP
#define BUSINESSBUILDING_HPP

#include "Building.hpp"

class BusinessBuilding : public Building {
	
	const glm::vec3 k_color = glm::vec3(0.0, 0.0, 1.0);

	public:
		BusinessBuilding();
		virtual ~BusinessBuilding();

	protected:
		
};

#endif