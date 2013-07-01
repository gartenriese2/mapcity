#ifndef LANDSTRASSE_HPP
#define LANDSTRASSE_HPP

#include "Road.hpp"

class Landstrasse : public Road {
	
	const float k_width = 10.0;
	const glm::vec3 k_color = glm::vec3(1.0,1.0,0.0);

	public:
		Landstrasse(const std::vector<glm::vec3>);
		virtual ~Landstrasse();
	
};

#endif