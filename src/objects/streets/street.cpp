#include "street.hpp"

#include "../../rendering/conversion.hpp"

#include <map>
#include "../../../resources/lanes.db"

Street::Street(const std::string & type)
  : m_type{type}
{
	LOG_ASSERT(k_streets.count(m_type) != 0, "Street with the name " + m_type + " does not exist.");
	m_config = k_streets.at(m_type);


}

std::string Street::getType() const {
	return m_type;
}

glm::vec4 Street::getColor() const {
	return glm::vec4(m_config.getColor(), 1.f);
}

bool Street::isDynamic() const {
	return false;
}

std::vector<std::shared_ptr<Path>> & Street::getPaths() {
	return m_paths;
}

const LaneConfig & Street::getConfig() const {
	return m_config;
}

StraightStreet::StraightStreet(const glm::vec3 & start, const glm::vec3 & end,
			const std::string & type)
  : Street{type},
	m_start{start},
	m_end{end}
{
	initPaths();
	initModelMatrix();
}

void StraightStreet::initModelMatrix() {
	const auto width = m_config.getTotalWidth();

	const auto scaling = gameToGraphics(glm::vec2(glm::length(m_end - m_start) * 0.5f, width * 0.5f));
	m_object.scale({scaling.x, scaling.y, 1.f});

	const auto angle = glm::atan((m_end - m_start).y, (m_end - m_start).x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo(gameToGraphics((m_start + m_end) * 0.5f));
}

void StraightStreet::initPaths() {
	const auto centers = m_config.getLaneCenters();
	const auto & directions = m_config.getDirections();
	std::vector<std::shared_ptr<Path>> paths;
	m_paths.reserve(centers.size());
	const auto n = glm::normalize(glm::vec3((m_end - m_start).y, (m_start - m_end).x, m_start.z));
	const glm::vec3 sideStart = m_start - m_config.getTotalWidth() * 0.5f * n;
	const glm::vec3 sideEnd = m_end - m_config.getTotalWidth() * 0.5f * n;
	for (auto i = 0u; i < centers.size(); ++i) {
		const auto s = sideStart + centers[i] * n;
		const auto e = sideEnd + centers[i] * n;
		if (directions[i]) {
			m_paths.emplace_back(std::make_shared<StraightPath>(s, e));
		} else {
			m_paths.emplace_back(std::make_shared<StraightPath>(e, s));
		}
	}
}
