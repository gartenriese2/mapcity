#include "ResidentialBuilding.hpp"

ResidentialBuilding::ResidentialBuilding() {

}

ResidentialBuilding::~ResidentialBuilding() {
	
}

void ResidentialBuilding::createHouseholds(int num) {

	for (int i = 0; i < num; i++) {
		households.push_back(Household());
	}

}