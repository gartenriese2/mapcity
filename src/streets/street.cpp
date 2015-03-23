#include "street.hpp"

StraightStreet::StraightStreet(const glm::vec3 & start, const glm::vec3 & end)
  : m_start{start},
	m_end{end}
{
}

void StraightStreet::initModelMatrix(const float width) {
	m_object.scale({glm::length(m_end - m_start) / 2.f, width / 2.f, 0.f});

	const float angle = glm::atan((m_end - m_start).y, (m_end - m_start).x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo((m_start + m_end) / 2.f);
}

StraightSmallStreet::StraightSmallStreet(const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet{start, end}
{
	initModelMatrix(k_width);
}

StraightMediumStreet::StraightMediumStreet(const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet{start, end}
{
	initModelMatrix(k_width);
}
