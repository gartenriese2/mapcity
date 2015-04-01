#include "laneconfig.hpp"

#include <MonoEngine/core/log.hpp>

#include <map>
#include <string>
#include "../../../resources/lanes.db"

LaneConfig::LaneConfig(const std::vector<std::string> & names, const std::vector<bool> & directions,
		const glm::vec3 & color)
  : m_directions{directions},
	m_color{color}
{
	for (const auto & name : names) {
		LOG_ASSERT(k_lanes.count(name) != 0, "Lane with the name " + name + " does not exist.");
		m_lanes.emplace_back(k_lanes.at(name));
	}
	LOG_ASSERT(m_lanes.size() == m_directions.size(), "Lanes and Directions Size don't match!");
}

float LaneConfig::getTotalWidth() const {
	auto width = 0.f;
	for (const auto & lane : m_lanes) {
		width += lane.width;
	}
	return width;
}

std::vector<float> LaneConfig::getLaneCenters() const {
	std::vector<float> centers;
	centers.reserve(m_lanes.size());
	auto widthCounter = 0.f;
	for (const auto & lane : m_lanes) {
		centers.emplace_back(widthCounter + lane.width * 0.5f);
		widthCounter += lane.width;
	}
	return centers;
}

const std::vector<Lane> & LaneConfig::getLanes() const {
	return m_lanes;
}

const std::vector<bool> & LaneConfig::getDirections() const {
	return m_directions;
}

const glm::vec3 & LaneConfig::getColor() const {
	return m_color;
}
