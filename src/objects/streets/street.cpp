#include "street.hpp"

#include "../../rendering/conversion.hpp"

void Street::addPaths(const std::vector<std::shared_ptr<Path>> & paths) {
	m_paths.insert(m_paths.end(), paths.begin(), paths.end());
}

std::vector<std::shared_ptr<Path>> & Street::getPaths() {
	return m_paths;
}

StraightStreet::StraightStreet(Manager & m, const glm::vec3 & start, const glm::vec3 & end)
  : Drawable{m},
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
	std::shared_ptr<Path> path = std::make_shared<StraightPath>(m, start, end);
	m_paths.emplace_back(path);
}

StraightMediumStreet::StraightMediumStreet(Manager & m, const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet{m, start, end}
{
	initModelMatrix(k_width);
	const auto offset = glm::normalize(glm::vec3((end - start).y, (start - end).x, start.z)) * k_width * 0.25f;
	std::shared_ptr<Path> path = std::make_shared<StraightPath>(m, start + offset, end + offset);
	m_paths.emplace_back(path);
	path = std::make_shared<StraightPath>(m, start - offset, end - offset);
	m_paths.emplace_back(path);

}
