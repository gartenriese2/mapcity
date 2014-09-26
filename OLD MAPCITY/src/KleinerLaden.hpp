#ifndef KLEINERLADEN_HPP
#define KLEINERLADEN_HPP

#include "BusinessBuilding.hpp"
#include "BusinessZone.hpp"

class KleinerLaden : public BusinessBuilding {
	
	static const unsigned short k_minFloors = 1;
	static const unsigned short k_maxFloors = 2;

	static constexpr float k_minWidth = 4.0;
	static constexpr float k_minLength = 6.0;
	static constexpr float k_maxWidth = 6.0;
	static constexpr float k_maxLength = 8.0;

	public:
		KleinerLaden(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~KleinerLaden();

		static float getMinWidth() { return k_minWidth; }
		static float getMinLength() { return k_minLength; }
	
};

class KleinerLadenZone : public BusinessZone {
	public:
		KleinerLadenZone(const vectorVec3 &);
		virtual ~KleinerLadenZone();

		void addBuilding();
		
};

#endif