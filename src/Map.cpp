#include "Map.hpp"

Map::Map(const int height, const int width) {
	
	m_height = height;
	m_width = width;

	m_hexagons = createHexagons();

}

Map::~Map() {

}

int Map::createHexagons() {

	m_xHexas = (int)ceil((m_width / hexaSideLength + 1) / 1.5);
	m_zHexas = (int)ceil(m_height / hexaHeight + 0.5);

	float x,z;

	//Spalte für Spalte von unten nach oben
	for (int i = 0; i < m_xHexas; i++) {
		for (int j = 0; j < m_zHexas; j++) {
			
			x = i * hexaSideLength * 1.5f;
			z = j * hexaHeight + i%2 * hexaHeight/2;

			m_hexaVector.push_back(Hexagon(glm::vec3(x,0,-z)));

		}
	}

	return static_cast<int>(m_hexaVector.size());

}

Hexagon & Map::getCorrespondingHexagon(const glm::vec3 & p) {

	if (p.x < 0 || p.x > m_width || -p.z < 0 || -p.z > m_height) {
		throw "Point not in Map";
	}

	int minCol = (int)floor((p.x/hexaSideLength - 1) / 1.5) + 1;
	int maxCol = (int)ceil((p.x/hexaSideLength + 1) / 1.5) - 1;
	int minRow = (int)floor(-p.z/hexaHeight - 1) + 1;
	int maxRow = (int)ceil(-p.z/hexaHeight + 0.5) - 1;

	for (int col = minCol; col <= maxCol; col++) {
		for (int row = minRow; row <= maxRow; row++)	{
			if (m_hexaVector[static_cast<unsigned long>(col * m_zHexas + row)].isInside(p)) 
				return m_hexaVector.at(static_cast<unsigned long>(col * m_zHexas + row));
		}
	}
	
	throw "No Hexagon found";

}