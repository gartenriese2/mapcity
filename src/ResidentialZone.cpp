#include "ResidentialZone.hpp"

ResidentialZone::ResidentialZone() {
	this->residents = 0;
	
}

ResidentialZone::~ResidentialZone() {

}

int ResidentialZone::getChildren() {

	int count = 0;
	getBuildings();
	return count;

}