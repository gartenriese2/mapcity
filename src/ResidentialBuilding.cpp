#include "ResidentialBuilding.hpp"

ResidentialBuilding::ResidentialBuilding() {
	setColor(k_color);
}

ResidentialBuilding::~ResidentialBuilding() {
	// delete households
}

void ResidentialBuilding::createHouseholds(int num) {

	for (int i = 0; i < num; i++) {
		m_householdVector.push_back(Household());
	}

}