#include "street.hpp"

#include "../../rendering/conversion.hpp"

Street::Street(std::unique_ptr<Path> path)
  : m_path{std::move(path)}
{
}

StraightStreet::StraightStreet(Manager & m, const glm::vec3 & start, const glm::vec3 & end)
  : Street(std::make_unique<StraightPath>(m, start, end)),
	Drawable{m},
	m_start{start},
	m_end{end}
{
}

void StraightStreet::initModelMatrix(const float width) {
	const auto scaling = gameToGraphics(glm::vec3{glm::length(m_end - m_start) * 0.5f, width * 0.5f, 0.f});
	m_object.scale(scaling);

	const auto angle = glm::atan((m_end - m_start).y, (m_end - m_start).x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo(gameToGraphics((m_start + m_end) * 0.5f));
}

StraightSmallStreet::StraightSmallStreet(Manager & m, const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet{m, start, end}
{
	initModelMatrix(k_width);
}

StraightMediumStreet::StraightMediumStreet(Manager & m, const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet{m, start, end}
{
	initModelMatrix(k_width);
}
