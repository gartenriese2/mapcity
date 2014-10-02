#include "residentialbuilding.hpp"

#include "../xml/buildingdatabase.hpp"
#include "../../engine/debug.hpp"
#include "../util/random.hpp"

ResidentialBuilding::ResidentialBuilding(unsigned int id) {

	if (!Building::s_database.idExists(id)) {

		Debug::log("ID " + std::to_string(id) + " does not exist");
		exit(EXIT_FAILURE);

	}

	m_numHouseholds = Random::get<unsigned int>(
		s_database.getMinHouseholds(id), s_database.getMaxHouseholds(id) + 1
	);

}

unsigned int ResidentialBuilding::getEmptyHouseholds() const {

	if (getOccupiedHouseholds() > m_numHouseholds) return 0;
	return m_numHouseholds - getOccupiedHouseholds();

}

unsigned int ResidentialBuilding::getOccupiedHouseholds() const {

	return static_cast<unsigned int>(m_households.size());

}

bool ResidentialBuilding::moveIn(const Household & household) {

	if (getEmptyHouseholds() == 0) return false;

	m_households.emplace_back(household);
	return true;

}
