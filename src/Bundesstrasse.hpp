#ifndef BUNDESSTRASSE_HPP
#define BUNDESSTRASSE_HPP

#include "Road.hpp"

class Bundesstrasse : public Road {
	
	const float k_width = 16.0;
	const glm::vec3 k_color = glm::vec3(1.0,0.0,0.0);

	public:
		Bundesstrasse(const std::vector<glm::vec3>);
		virtual ~Bundesstrasse();
	
};

#endif