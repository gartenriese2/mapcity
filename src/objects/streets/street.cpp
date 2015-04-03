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
	initDrawables();
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

void StraightStreet::initDrawables() {
	const auto angle = glm::atan((m_end - m_start).y, (m_end - m_start).x);
	const auto n = glm::normalize(glm::vec3((m_end - m_start).y, (m_start - m_end).x, m_start.z));
	const auto centers = m_config.getLaneCenters();
	const auto & lanes = m_config.getLanes();
	auto sideStart = -m_config.getTotalWidth() * 0.5f;
	for (auto i = 0u; i < lanes.size(); ++i) {
		m_drawables.emplace_back(std::make_shared<Drawable>());
		auto & drawable = m_drawables[i];
		drawable->type = m_type;
		drawable->color = glm::vec4(lanes[i].color, 1.f);
		drawable->renderType = RenderTypeName::MULTICOLOR_QUAD;
		drawable->dynamic = false;
		drawable->unicolored = false;
		const auto scaling = gameToGraphics(glm::vec2(glm::length(m_end - m_start) * 0.5f,
				lanes[i].width * 0.5f));
		drawable->object.scale({scaling.x, scaling.y, 1.f});
		drawable->object.rotate(angle, {0.f, 0.f, 1.f});
		const auto offset = (sideStart + centers[i]) * glm::vec2(n.x, n.y);
		drawable->object.moveTo(gameToGraphics((m_start + m_end) * 0.5f + glm::vec3(offset, 0.f)));
	}
}
