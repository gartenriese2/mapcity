#include "ResidentialBuilding.hpp"

ResidentialBuilding::ResidentialBuilding() {
	setColor(k_color);
}

ResidentialBuilding::~ResidentialBuilding() {
	// delete households
}

void ResidentialBuilding::createHouseholds(const int num) {

	for (int i = 0; i < num; i++) {
		m_householdVector.push_back(Household());
	}

}

unsigned int ResidentialBuilding::getResidents() const {

	unsigned int res = 0;
	for (auto h : m_householdVector) {

		res += h.getResidents();

	}
	return res;

}