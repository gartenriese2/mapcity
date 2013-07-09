#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "glm.h"
#include <vector>
#include <iostream>
#include "Zone.hpp"
#include "ResidentialZone.hpp"

const float hexaSideLength = 100.f;
const float hexaHeight = hexaSideLength * static_cast<float>(sqrt(3.f));

class Hexagon {
	
	public:
	
		Hexagon(const glm::vec3 &);
		~Hexagon();

		const glm::vec3 & getCenter() const { return m_center; }
		const glm::vec3 & getLeft() const { return m_vertices[0]; }
		const vectorVec3 & getVertices() const { return m_vertices; }
		
		bool isInside(glm::vec3) const;

	private:

		glm::vec3 m_center;
		vectorVec3 m_vertices;

		void setVertices();

};

#endif
