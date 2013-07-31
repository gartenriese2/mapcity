#ifndef GROSSERLADEN_HPP
#define GROSSERLADEN_HPP

#include "BusinessBuilding.hpp"
#include "BusinessZone.hpp"

class GrosserLaden : public BusinessBuilding {
	
	static const unsigned short k_minFloors = 1;
	static const unsigned short k_maxFloors = 2;

	static constexpr float k_minWidth = 10.0;
	static constexpr float k_minLength = 20.0;
	static constexpr float k_maxWidth = 20.0;
	static constexpr float k_maxLength = 40.0;

	public:
		GrosserLaden(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~GrosserLaden();

		static float getMinWidth() { return k_minWidth; }
		static float getMinLength() { return k_minLength; }
	
};

class GrosserLadenZone : public BusinessZone {
	public:
		GrosserLadenZone(const vectorVec3 &);
		virtual ~GrosserLadenZone();

		void addBuilding();
		
};

#endif