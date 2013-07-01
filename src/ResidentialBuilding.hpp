#ifndef RESIDENTIALBUILDING_HPP
#define RESIDENTIALBUILDING_HPP

#include "Building.hpp"
#include "Household.hpp"

class ResidentialBuilding : public Building {
	
	const glm::vec3 k_color = glm::vec3(0.0, 1.0, 0.0);

	public:
		ResidentialBuilding();
		virtual ~ResidentialBuilding();
		std::vector<Household> getHouseholds() const { return m_householdVector; }
	protected:
		void createHouseholds(int);
		
		std::vector<Household> m_householdVector;
};

#endif