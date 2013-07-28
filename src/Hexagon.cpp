#include "Hexagon.hpp"

unsigned long Hexagon::s_queriedID = 0;

Hexagon::Hexagon(const glm::vec3 & center) {

	m_center = center;
	setVertices();
	ID = ObjectContainer::instance().addHexagon(center, getLeft(), glm::vec3(1,1,1));

}

Hexagon::~Hexagon() {
	
	m_vertices.clear();

}

void Hexagon::setVertices() {
	
	m_vertices.push_back(m_center + glm::vec3(-hexaSideLength,0,0));
	m_vertices.push_back(m_center + glm::vec3(-hexaSideLength/2,0,hexaHeight/2));
	m_vertices.push_back(m_center + glm::vec3(hexaSideLength/2,0,hexaHeight/2));
	m_vertices.push_back(m_center + glm::vec3(hexaSideLength,0,0));
	m_vertices.push_back(m_center + glm::vec3(hexaSideLength/2,0,-hexaHeight/2));
	m_vertices.push_back(m_center + glm::vec3(-hexaSideLength/2,0,-hexaHeight/2));

}

bool Hexagon::isInside(glm::vec3 p) const {

	// transform point to lower right quadrant
	if (p.z < m_center.z) p.z += 2*(m_center.z-p.z);
	if (p.x < m_center.x) p.x += 2*(m_center.x-p.x);

	// check against bounding box
	if (p.x > m_vertices[3].x) return false;
	if (p.z > m_vertices[2].z) return false;
	if (p.x < m_vertices[2].x) return true;

	// normal to sloped edge
	glm::vec3 n = glm::vec3(-hexaHeight/2, 0, -hexaSideLength/2);

	// vector from right vertex to point p
	glm::vec3 v = m_vertices[3] - p;

	if (glm::dot(n,v) > 0) return false;
	return true;

}

void Hexagon::query() {

	if (m_isQueried) {
		ObjectContainer::instance().changeHexagonColor(ID, k_defaultColor);
		m_isQueried = false;
	} else {
		ObjectContainer::instance().changeHexagonColor(ID, k_clickedColor);
		m_isQueried = true;
	}

}