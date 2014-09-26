#ifndef MIETSHAUS_HPP
#define MIETSHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Mietshaus : public ResidentialBuilding {
	
	static const unsigned short k_minFloors = 3;
	static const unsigned short k_maxFloors = 8;
	static const unsigned short k_numHouseholds = 4;

	static constexpr float k_minWidth = 8.0;
	static constexpr float k_minLength = 16.0;
	static constexpr float k_maxWidth = 12.0;
	static constexpr float k_maxLength = 24.0;

	public:
		Mietshaus(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~Mietshaus();

		static float getMinWidth() { return k_minWidth; }
		static float getMinLength() { return k_minLength; }
	
};

class MietshausZone : public ResidentialZone {
	public:
		MietshausZone(const vectorVec3 &);
		virtual ~MietshausZone();

		void addBuilding();
		
};

#endif