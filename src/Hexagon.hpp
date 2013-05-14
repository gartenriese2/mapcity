#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "../glm-0.9.4.3/glm/glm.hpp"
#include <vector>
#include <iostream>
#include "ResidentialZone.hpp"
// #include "IndustrialZone.hpp"

const float hexaSideLength = 100.f;
const float hexaHeight = hexaSideLength * sqrt(3.f);

class Hexagon
{
public:
	Hexagon(glm::vec3);
	~Hexagon();
	inline glm::vec3 getCenter() { return this->center; };
	const std::vector<glm::vec3>& getVertices() const { return vertices; }
	// const std::vector<Hexagon>& getNeighbors() const { return neighbors; }
	bool isInside(glm::vec3 p);
	
	inline void addZone(Zone * z) { genericZones.push_back(z); }
	inline void addResidentialZone(ResidentialZone z) { this->residentialZones.push_back(z); /*addZone(z);*/ }
	// inline void addIndustrialZone(IndustrialZone z) { this->industrialZones.push_back(z); /*addZone(z);*/ }
	
	// template <class T> void deleteZone(T);

	int getChildren();
	int getResidents();

	int countUndevelopedZones();
private:
	glm::vec3 center;
	std::vector<glm::vec3> vertices;
	// std::vector<Hexagon> neighbors;

	std::vector<Zone*> genericZones;
	std::vector<ResidentialZone> residentialZones;
	// std::vector<IndustrialZone> industrialZones;

	void setVertices();
	// template <class T> inline void addZone(T z) { this->genericZones.push_back(z); };
};

#endif
