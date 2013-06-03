#ifndef MAP_HPP
#define MAP_HPP

#include "Hexagon.hpp"
#include <vector>
#include <iostream>

class Map {
public:
	Map(int, int);
	~Map();

	int getHeight();
	int getWidth();
	int getNumberOfHexagons();
	std::vector<Hexagon> getHexaVector();
	Hexagon& getCorrespondingHexagon(glm::vec3);
	
private:

	int height;
	int width;
	int hexagons;
	int xHexas;
	int zHexas;
	std::vector<Hexagon> hexaVector;

	int createHexagons();

};

#endif
