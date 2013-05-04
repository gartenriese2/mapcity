#include "Zone.hpp"

int Zone::count = 0;

Zone::Zone() {
	
	this->ID = ++Zone::count;
	
}

Zone::~Zone() {
	this->bounding.clear();
}

void Zone::setArea() {
	this->area = 0.f;
	for (int i = 0; i < bounding.size() - 1; i++) {
		this->area += (bounding[i].y + bounding[i+1].y) / 2 * (bounding[i+1].x - bounding[i].x);
	}
	this->area += (bounding[bounding.size()-1].y + bounding[0].y) / 2 * (bounding[0].x - bounding[bounding.size()-1].x);
}

void Zone::setCenter() {
	
	float centroidX = 0.f;
	float centroidY = 0.f;

	for (int i = 0; i < bounding.size() - 1; i++) {
		centroidX += (bounding[i].x + bounding[i+1].x) * (bounding[i].x * bounding[i+1].y - bounding[i+1].x * bounding[i].y);
		centroidY += (bounding[i].y + bounding[i+1].y) * (bounding[i].x * bounding[i+1].y - bounding[i+1].x * bounding[i].y);
	}
	centroidX += (bounding[bounding.size()-1].x + bounding[0].x) 
			* (bounding[bounding.size()-1].x * bounding[0].y - bounding[0].x * bounding[bounding.size()-1].y);
	centroidY += (bounding[bounding.size()-1].y + bounding[0].y) 
			* (bounding[bounding.size()-1].x * bounding[0].y - bounding[0].x * bounding[bounding.size()-1].y);

	this->center = glm::vec3(-centroidX / (6*getArea()), -centroidY / (6*getArea()), 0);

}

void Zone::deleteBuilding(Building b) {
	for (int i = 0; i < this->buildings.size(); i++) {
		if (this->buildings[i]->getID() == b.getID()) {
			this->buildings.erase(this->buildings.begin()+i);
			break;
		}
	}
}