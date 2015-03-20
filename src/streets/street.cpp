#include "street.hpp"

Street::Street() {

}

StraightStreet::StraightStreet(const glm::vec3 & start, const glm::vec3 & end)
  : m_start{start},
	m_end{end}
{

}

std::vector<glm::vec3> StraightStreet::calculateVertices(const float width) const {

	const auto dir = m_end - m_start;
	const auto nDir = glm::normalize(glm::vec3(dir.y, -dir.x, 0.f));

	std::vector<glm::vec3> vertices;
	vertices.emplace_back(m_start + width * 0.5f * nDir);
	vertices.emplace_back(m_end + width * 0.5f * nDir);
	vertices.emplace_back(m_end - width * 0.5f * nDir);
	vertices.emplace_back(m_start - width * 0.5f * nDir);
	return vertices;

}

StraightSmallStreet::StraightSmallStreet(const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet{start, end}
{
	m_object.scale({glm::length(end - start) / 2.f, k_width / 2.f, 0.f});

	const float angle = glm::atan((end - start).y, (end - start).x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo((start + end) / 2.f);
}
