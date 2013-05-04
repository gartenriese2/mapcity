#include "Hexagon.hpp"

Hexagon::Hexagon(glm::vec3 center) {

	this->center = center;
	setVertices();

}

Hexagon::~Hexagon() {
	
	this->vertices.clear();
	// this->neighbors.clear();

}

void Hexagon::setVertices() {
	
	vertices.push_back(center + glm::vec3(-hexaSideLength,0,0));
	vertices.push_back(center + glm::vec3(-hexaSideLength/2,hexaHeight/2,0));
	vertices.push_back(center + glm::vec3(hexaSideLength/2,hexaHeight/2,0));
	vertices.push_back(center + glm::vec3(hexaSideLength,0,0));
	vertices.push_back(center + glm::vec3(hexaSideLength/2,-hexaHeight/2,0));
	vertices.push_back(center + glm::vec3(-hexaSideLength/2,-hexaHeight/2,0));

}

bool Hexagon::isInside(glm::vec3 p) {

	// transform point to upper right quadrant
	if (p.y < center.y) p.y += 2*(center.y-p.y);
	if (p.x < center.x) p.x += 2*(center.x-p.x);

	// check against bounding box
	if (p.x > vertices[3].x) return false;
	if (p.y > vertices[2].y) return false;
	if (p.x < vertices[2].x) return true;

	// normal to sloped edge
	glm::vec3 n = glm::vec3(-hexaHeight/2, -hexaSideLength/2, 0);

	// vector from right vertex to point p
	glm::vec3 v = glm::vec3(p.x - (vertices[3].x), p.y - center.y, 0);

	if (glm::dot(n,v) < 0) return false;
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