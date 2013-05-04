#include "Building.hpp"

int Building::count = 0;

Building::Building() {

	this->ID = ++Building::count;

}

Building::~Building() {

}

void Building::createOutline() {

	outline.clear();
	

}