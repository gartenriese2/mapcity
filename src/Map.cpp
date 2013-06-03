#include "Map.hpp"

Map::Map(int height, int width) {
	
	this->height = height;
	this->width = width;

	this->hexagons = createHexagons();

}

Map::~Map() {

}

int Map::getHeight() {
	return this->height;
}

int Map::getWidth() {
	return this->width;
}

std::vector<Hexagon> Map::getHexaVector() {
	return this->hexaVector;
}

int Map::createHexagons() {

	xHexas = (int)ceil((this->width / hexaSideLength + 1) / 1.5);
	zHexas = (int)ceil(this->height / hexaHeight + 0.5);

	float x,z;

	//Spalte für Spalte von unten nach oben
	for (int i = 0; i < xHexas; i++) {
		for (int j = 0; j < zHexas; j++) {
			
			x = i * hexaSideLength * 1.5;
			z = j * hexaHeight + i%2 * hexaHeight/2;

			hexaVector.push_back(Hexagon(glm::vec3(x,0,-z)));

		}
	}

	return this->hexaVector.size();

}

Hexagon& Map::getCorrespondingHexagon(glm::vec3 p) {

	if (p.x < 0 || p.x > this->width || -p.z < 0 || -p.z > this->height) {
		throw "Point not in Map";
	}

	int minCol = (int)floor((p.x/hexaSideLength - 1) / 1.5) + 1;
	int maxCol = (int)ceil((p.x/hexaSideLength + 1) / 1.5) - 1;
	int minRow = (int)floor(-p.z/hexaHeight - 1) + 1;
	int maxRow = (int)ceil(-p.z/hexaHeight + 0.5) - 1;

	for (int col = minCol; col <= maxCol; col++) {
		for (int row = minRow; row <= maxRow; row++)	{
			if (hexaVector[col * zHexas + row].isInside(p)) return hexaVector.at(col * zHexas + row);
		}
	}

	// for (int i = 0; i < hexaVector.size(); i++) {
	// 	if (hexaVector[i].isInside(p)) {
	// 		return hexaVector[i];
	// 	}
	// }
	
	throw "No Hexagon found";

}