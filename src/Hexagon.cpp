#include "Hexagon.hpp"

Hexagon::Hexagon(glm::vec3 center) {

	this->center = center;
	setVertices();
	ObjectContainer::instance().addHexagon(center, getLeft(), glm::vec3(1,1,1));

}

Hexagon::~Hexagon() {
	
	this->vertices.clear();
	// this->neighbors.clear();

}

void Hexagon::setVertices() {
	
	vertices.push_back(center + glm::vec3(-hexaSideLength,0,0));
	vertices.push_back(center + glm::vec3(-hexaSideLength/2,0,hexaHeight/2));
	vertices.push_back(center + glm::vec3(hexaSideLength/2,0,hexaHeight/2));
	vertices.push_back(center + glm::vec3(hexaSideLength,0,0));
	vertices.push_back(center + glm::vec3(hexaSideLength/2,0,-hexaHeight/2));
	vertices.push_back(center + glm::vec3(-hexaSideLength/2,0,-hexaHeight/2));

}

bool Hexagon::isInside(glm::vec3 p) {

	// transform point to lower right quadrant
	if (p.z < center.z) p.z += 2*(center.z-p.z);
	if (p.x < center.x) p.x += 2*(center.x-p.x);

	// check against bounding box
	if (p.x > vertices[3].x) return false;
	if (p.z > vertices[2].z) return false;
	if (p.x < vertices[2].x) return true;

	// normal to sloped edge
	glm::vec3 n = glm::vec3(-hexaHeight/2, 0, -hexaSideLength/2);

	// vector from right vertex to point p
	glm::vec3 v = vertices[3] - p;

	if (glm::dot(n,v) > 0) return false;
	return true;

}

// template <class T> void Hexagon::deleteZone(T zone) {
	
// 	// for (int i = 0; i < this->genericZones.size(); i++) {
// 	// 	if (this->genericZones[i].getID() == zone.getID()) {
// 	// 		this->genericZones.erase(this->genericZones.begin()+i);
// 	// 		break;
// 	// 	}
// 	// }
// 	for (int i = 0; i < this->residentialZones.size(); i++) {
// 		if (this->residentialZones[i].getID() == zone.getID()) {
// 			this->residentialZones.erase(this->residentialZones.begin()+i);
// 			break;
// 		}
// 	}
// 	for (int i = 0; i < this->industrialZones.size(); i++) {
// 		if (this->industrialZones[i].getID() == zone.getID()) {
// 			this->industrialZones.erase(this->industrialZones.begin()+i);
// 			break;
// 		}
// 	}
	
// }

int Hexagon::getChildren() {

	int count = 0;

	for (std::vector<ResidentialZone>::iterator it = residentialZones.begin(); it != residentialZones.end(); it++) {
		count += (*it).getChildren();
	}

	return count;

}

int Hexagon::getResidents() {

	int count = 0;
	for (std::vector<Zone*>::iterator it = genericZones.begin(); it != genericZones.end(); it++) {
		if ( dynamic_cast<ResidentialZone*>( *it ) ) {		// check if this zone is a residential zone
			ResidentialZone *p = ( ResidentialZone* )(*it); 	// enable derived functions
			count += p->getResidents();						//(dynamic_cast<ResidentialZone*>(z))->getResidents();
		}
	}

	return count;

}

int Hexagon::countUndevelopedZones() {

	int undeveloped = 0;
	for (int i = 0; i < genericZones.size(); i++) {
		if (!genericZones[i]->isDeveloped()) undeveloped++;
	}
	return undeveloped;

}