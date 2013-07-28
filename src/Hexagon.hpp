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
		const unsigned long getID() const { return ID; }
		const unsigned long getQueriedID() const { return s_queriedID; }
		void setQueriedID(unsigned long i) { s_queriedID = i; }
		
		bool isInside(glm::vec3) const;
		void query();

	protected:

		const glm::vec3 k_defaultColor = glm::vec3(1,1,1);
		const glm::vec3 k_clickedColor = glm::vec3(0.6,0.6,0.6);

		unsigned long ID;
		glm::vec3 m_center;
		vectorVec3 m_vertices;

		bool m_isQueried = false;
		static unsigned long s_queriedID;

		void setVertices();

};

#endif
