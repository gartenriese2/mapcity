#ifndef KLEINERLADEN_HPP
#define KLEINERLADEN_HPP

#include "BusinessBuilding.hpp"
#include "BusinessZone.hpp"

class KleinerLaden : public BusinessBuilding {
	
	const float k_minHeight = 4.0;
	const float k_maxHeight = 10.0;

	public:
		KleinerLaden(const glm::vec3, const glm::vec3, const glm::vec3);
		virtual ~KleinerLaden();
	
};

class KleinerLadenZone : public BusinessZone {
	public:
		KleinerLadenZone(const vectorVec3);
		virtual ~KleinerLadenZone();
		
};

#endif