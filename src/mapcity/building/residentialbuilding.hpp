#ifndef _RESIDENTIALBUILDING_
#define _RESIDENTIALBUILDING_

#include "building.hpp"
#include "../people/household.hpp"

#include <vector>

class ResidentialBuilding : public Building {

	public:

		ResidentialBuilding() {}
		ResidentialBuilding(unsigned int, const glm::vec3 & = {0.f, 0.f, 0.f}, bool = false);

		unsigned int getEmptyHouseholds() const;
		unsigned int getOccupiedHouseholds() const;
		const std::vector<Household> & getHouseholds() const { return m_households; }

		bool moveIn(const Household &);

	private:

		std::vector<Household> m_households;
		unsigned int m_numHouseholds;

};

#endif // _RESIDENTIALBUILDING_
