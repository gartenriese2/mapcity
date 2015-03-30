#include "terrain.hpp"

#include "../../rendering/conversion.hpp"

Terrain::Terrain(const glm::vec3 & start, const glm::vec3 & end)
  : m_start{start},
	m_end{end}
{
	initModelMatrix();
}

void Terrain::initModelMatrix() {
	const auto scaling = gameToGraphics(glm::vec2((m_end.x - m_start.x) * 0.5f,
			(m_end.y - m_start.y) * 0.5f));
	m_object.scale({scaling.x, scaling.y, 1.f});
	m_object.moveTo(gameToGraphics(m_start + m_end) * 0.5f);
}
