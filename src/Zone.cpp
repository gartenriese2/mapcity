#include "Zone.hpp"

int Zone::count = 0;

Zone::Zone() {
	
	this->ID = ++Zone::count;
	isBuilt = false;
	
}

Zone::~Zone() {
	this->bounding.clear();
}

void Zone::setArea() {
	this->area = 0.f;
	for (int i = 0; i < bounding.size() - 1; i++) {
		this->area += (bounding[i].z + bounding[i+1].z) / 2 * (bounding[i+1].x - bounding[i].x);
	}
	this->area += (bounding[bounding.size()-1].z + bounding[0].z) / 2 * (bounding[0].x - bounding[bounding.size()-1].x);
}

void Zone::setCenter() {
	
	float centroidX = 0.f;
	float centroidZ = 0.f;

	for (int i = 0; i < bounding.size() - 1; i++) {
		centroidX += (bounding[i].x + bounding[i+1].x) * (bounding[i].x * bounding[i+1].z - bounding[i+1].x * bounding[i].z);
		centroidZ += (bounding[i].z + bounding[i+1].z) * (bounding[i].x * bounding[i+1].z - bounding[i+1].x * bounding[i].z);
	}
	centroidX += (bounding[bounding.size()-1].x + bounding[0].x) 
			* (bounding[bounding.size()-1].x * bounding[0].z - bounding[0].x * bounding[bounding.size()-1].z);
	centroidZ += (bounding[bounding.size()-1].z + bounding[0].z) 
			* (bounding[bounding.size()-1].x * bounding[0].z - bounding[0].x * bounding[bounding.size()-1].z);

	this->center = glm::vec3(-centroidX / (6*getArea()), 0, -centroidZ / (6*getArea()));

}

void Zone::deleteBuilding(Building b) {
	for (int i = 0; i < this->buildings.size(); i++) {
		if (this->buildings[i]->getID() == b.getID()) {
			this->buildings.erase(this->buildings.begin()+i);
			break;
		}
	}
}