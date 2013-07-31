#ifndef EINFAMILIENHAUS_HPP
#define EINFAMILIENHAUS_HPP

#include "ResidentialBuilding.hpp"
#include "ResidentialZone.hpp"

class Einfamilienhaus : public ResidentialBuilding {
	
	private:

		static const unsigned short k_minFloors = 1;
		static const unsigned short k_maxFloors = 3;
		static const unsigned short k_numHouseholds = 1;

		static constexpr float k_minWidth = 4.0;
		static constexpr float k_minLength = 6.0;
		static constexpr float k_maxWidth = 6.0;
		static constexpr float k_maxLength = 8.0;

	public:
		Einfamilienhaus(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		virtual ~Einfamilienhaus();

		static float getMinWidth() { return k_minWidth; }
		static float getMinLength() { return k_minLength; }
	
};

class EinfamilienhausZone : public ResidentialZone {
	
	public:
		
		EinfamilienhausZone(const vectorVec3 &);
		virtual ~EinfamilienhausZone();

		void addBuilding();
		
};

#endif