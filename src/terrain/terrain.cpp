#include "terrain.hpp"

Terrain::Terrain(const glm::vec3 & start, const glm::vec3 & end)
  : m_start{start},
	m_end{end}
{
	initModelMatrix();
}

void Terrain::initModelMatrix() {
	m_object.scale({(m_end.x - m_start.x) / 2.f, (m_end.y - m_start.y) / 2.f, 0.f});
	m_object.moveTo((m_start + m_end) / 2.f);
}
