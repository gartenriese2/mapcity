#include "ResidentialZone.hpp"

ResidentialZone::ResidentialZone() {
	setColor(k_color);
}

ResidentialZone::~ResidentialZone() {

}

unsigned int ResidentialZone::getResidents() const {

	unsigned int res = 0;
	for (auto b : getBuildings()) {

		res += b->getResidents();

	}
	return res;

}