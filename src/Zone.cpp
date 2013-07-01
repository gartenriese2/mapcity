#include "Zone.hpp"

Zone::Zone() {
	
}

Zone::~Zone() {
	m_bounding.clear();
}

void Zone::createObject() {
	m_ID = ObjectContainer::instance().addZone(m_bounding, m_center, m_color);
}

void Zone::setArea() {
	m_area = 0.f;
	for (int i = 0; i < m_bounding.size() - 1; i++) {
		m_area += (m_bounding[i].z + m_bounding[i+1].z) / 2 * (m_bounding[i+1].x - m_bounding[i].x);
	}
	m_area += (m_bounding[m_bounding.size()-1].z + m_bounding[0].z) / 2 * (m_bounding[0].x - m_bounding[m_bounding.size()-1].x);
}

void Zone::setCenter() {
	
	float centroidX = 0.f;
	float centroidZ = 0.f;

	for (int i = 0; i < m_bounding.size() - 1; i++) {
		centroidX += (m_bounding[i].x + m_bounding[i+1].x) * (m_bounding[i].x * m_bounding[i+1].z - m_bounding[i+1].x * m_bounding[i].z);
		centroidZ += (m_bounding[i].z + m_bounding[i+1].z) * (m_bounding[i].x * m_bounding[i+1].z - m_bounding[i+1].x * m_bounding[i].z);
	}
	centroidX += (m_bounding[m_bounding.size()-1].x + m_bounding[0].x) 
			* (m_bounding[m_bounding.size()-1].x * m_bounding[0].z - m_bounding[0].x * m_bounding[m_bounding.size()-1].z);
	centroidZ += (m_bounding[m_bounding.size()-1].z + m_bounding[0].z) 
			* (m_bounding[m_bounding.size()-1].x * m_bounding[0].z - m_bounding[0].x * m_bounding[m_bounding.size()-1].z);

	m_center = glm::vec3(-centroidX / (6*getArea()), m_bounding[0].y, -centroidZ / (6*getArea()));

}