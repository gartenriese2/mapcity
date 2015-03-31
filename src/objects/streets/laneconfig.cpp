#include "laneconfig.hpp"

LaneConfig::LaneConfig(const std::vector<Lane> & lanes)
  : m_lanes{lanes}
{}

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
