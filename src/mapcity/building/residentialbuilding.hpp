#ifndef _RESIDENTIALBUILDING_
#define _RESIDENTIALBUILDING_

#include "building.hpp"
#include "../people/household.hpp"

#include <vector>

class ResidentialBuilding : public Building {

	public:

		ResidentialBuilding() {}
		ResidentialBuilding(unsigned int);

		unsigned int getEmptyHouseholds() const;
		unsigned int getOccupiedHouseholds() const;

		bool moveIn(const Household &);

	private:

		std::vector<Household> m_households;
		unsigned int m_numHouseholds;

};

#endif // _RESIDENTIALBUILDING_
