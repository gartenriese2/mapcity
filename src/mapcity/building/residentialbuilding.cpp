#include "residentialbuilding.hpp"

#include "../xml/buildingdatabase.hpp"
#include "../../engine/debug.hpp"
#include "../util/random.hpp"

ResidentialBuilding::ResidentialBuilding(unsigned int id) {

	if (!Building::s_database.idExists(id)) {

		Debug::log("ID " + std::to_string(id) + " does not exist");
		exit(EXIT_FAILURE);

	}

	if (s_database.hasElement(id, "minHouseholds") && s_database.hasElement(id, "maxHouseholds")) {
		
		m_numHouseholds = Random::get(
			s_database.getUnsignedValue(id, "minHouseholds"),
			s_database.getUnsignedValue(id, "maxHouseholds")
		);

	} else if (s_database.hasElement(id, "minHouseholdsPerFloor")
		&& s_database.hasElement(id, "maxHouseholdsPerFloor")
		&& s_database.hasElement(id, "minFloors") && s_database.hasElement(id, "maxFloors")) {

		const unsigned int minFloors {s_database.getUnsignedValue(id, "minFloors")};
		const unsigned int maxFloors {s_database.getUnsignedValue(id, "maxFloors")};
		const unsigned int floors {Random::get(minFloors, maxFloors)};

		const unsigned int minHouseholdsPerFloor {s_database.getUnsignedValue(id, "minHouseholdsPerFloor")};
		const unsigned int maxHouseholdsPerFloor {s_database.getUnsignedValue(id, "maxHouseholdsPerFloor")};
		const unsigned int householdsPerFloor {Random::get(minHouseholdsPerFloor, maxHouseholdsPerFloor)};

		m_numHouseholds = floors * householdsPerFloor;

	} else {

		Debug::log("No variables found to determine number of households");
		exit(EXIT_FAILURE);

	}
	

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
