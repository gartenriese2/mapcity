#include "residentialbuilding.hpp"

#include "../xml/buildingdatabase.hpp"
#include "../../engine/debug.hpp"
#include "../util/random.hpp"

ResidentialBuilding::ResidentialBuilding(unsigned int id, const glm::vec3 & pos, bool hasParking)
  : Building{pos, hasParking}
{

	if (!Building::s_buildingDatabase.idExists(id)) {

		Debug::log("ID " + std::to_string(id) + " does not exist");
		exit(EXIT_FAILURE);

	}

	if (s_buildingDatabase.hasElement(id, "minHouseholds") && s_buildingDatabase.hasElement(id, "maxHouseholds")) {
		
		m_numHouseholds = Random::get(
			s_buildingDatabase.getValue<unsigned int>(id, "minHouseholds"),
			s_buildingDatabase.getValue<unsigned int>(id, "maxHouseholds")
		);

	} else if (s_buildingDatabase.hasElement(id, "minHouseholdsPerFloor")
		&& s_buildingDatabase.hasElement(id, "maxHouseholdsPerFloor")
		&& s_buildingDatabase.hasElement(id, "minFloors") && s_buildingDatabase.hasElement(id, "maxFloors")) {

		const unsigned int minFloors {s_buildingDatabase.getValue<unsigned int>(id, "minFloors")};
		const unsigned int maxFloors {s_buildingDatabase.getValue<unsigned int>(id, "maxFloors")};
		const unsigned int floors {Random::get(minFloors, maxFloors)};

		const unsigned int minHouseholdsPerFloor {s_buildingDatabase.getValue<unsigned int>(id, "minHouseholdsPerFloor")};
		const unsigned int maxHouseholdsPerFloor {s_buildingDatabase.getValue<unsigned int>(id, "maxHouseholdsPerFloor")};
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
