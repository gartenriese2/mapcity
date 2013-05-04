#ifndef RESIDENTIALBUILDING_HPP
#define RESIDENTIALBUILDING_HPP

#include "Building.hpp"
#include "Household.hpp"

class ResidentialBuilding : public Building {
	public:
		ResidentialBuilding();
		~ResidentialBuilding();
		inline std::vector<Household> getHouseholds() { return households; }
	private:

		std::vector<Household> households;
	protected:
		void createHouseholds(int);
};

#endif