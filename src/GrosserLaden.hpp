#ifndef GROSSERLADEN_HPP
#define GROSSERLADEN_HPP

#include "BusinessBuilding.hpp"
#include "BusinessZone.hpp"

class GrosserLaden : public BusinessBuilding {
	
	const float k_minHeight = 6.0;
	const float k_maxHeight = 12.0;

	public:
		GrosserLaden(const glm::vec3, const glm::vec3, const glm::vec3);
		virtual ~GrosserLaden();
	
};

class GrosserLadenZone : public BusinessZone {
	public:
		GrosserLadenZone(const std::vector<glm::vec3>);
		virtual ~GrosserLadenZone();
		
};

#endif