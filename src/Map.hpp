#ifndef MAP_HPP
#define MAP_HPP

#include "Hexagon.hpp"
#include <vector>
#include <iostream>

class Map {

	public:
	
		Map(const int, const int);
		~Map();

		int getHeight() const { return m_height; }
		int getWidth() const { return m_width; }
		int getNumberOfHexagons() const { return m_hexagons; }
		const std::vector<Hexagon> & getHexaVector() const { return m_hexaVector; }
		Hexagon & getCorrespondingHexagon(const glm::vec3 &);
	
	private:

		int m_height;
		int m_width;
		int m_hexagons;
		int m_xHexas;
		int m_zHexas;
		std::vector<Hexagon> m_hexaVector;

		int createHexagons();

};

#endif
