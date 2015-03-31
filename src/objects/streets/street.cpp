#include "street.hpp"

#include "../../rendering/conversion.hpp"

#include <map>
#include "../../../resources/lanes.db"

void Street::addPaths(const std::vector<std::shared_ptr<Path>> & paths) {
	m_paths.insert(m_paths.end(), paths.begin(), paths.end());
}

std::vector<std::shared_ptr<Path>> & Street::getPaths() {
	return m_paths;
}

StraightStreet::StraightStreet(const glm::vec3 & start, const glm::vec3 & end)
  : m_start{start},
	m_end{end}
{
}

void StraightStreet::initModelMatrix() {
	const auto width = m_lanes.getTotalWidth();

	const auto scaling = gameToGraphics(glm::vec2(glm::length(m_end - m_start) * 0.5f, width * 0.5f));
	m_object.scale({scaling.x, scaling.y, 1.f});

	const auto angle = glm::atan((m_end - m_start).y, (m_end - m_start).x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo(gameToGraphics((m_start + m_end) * 0.5f));
}

StraightSmallStreet::StraightSmallStreet(const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet(start, end)
{
	m_lanes = LaneConfig({k_lanes.at("SmallSidewalk"), k_lanes.at("SmallStreet"),
			k_lanes.at("SmallStreet"), k_lanes.at("SmallSidewalk")});

	initModelMatrix();
	std::shared_ptr<Path> path = std::make_shared<StraightPath>(start, end);
	m_paths.emplace_back(std::move(path));
}

StraightMediumStreet::StraightMediumStreet(const glm::vec3 & start, const glm::vec3 & end)
  : StraightStreet(start, end)
{
	m_lanes = LaneConfig({k_lanes.at("MediumSidewalk"), k_lanes.at("MediumStreet"),
			k_lanes.at("MediumStreet"), k_lanes.at("MediumSidewalk")});

	initModelMatrix();
	const auto offset = glm::normalize(glm::vec3((end - start).y, (start - end).x, start.z))
			* m_lanes.getTotalWidth() * 0.25f;
	std::shared_ptr<Path> path = std::make_shared<StraightPath>(start + offset, end + offset);
	m_paths.emplace_back(std::move(path));
	path = std::make_shared<StraightPath>(end - offset, start - offset);
	m_paths.emplace_back(std::move(path));
}
