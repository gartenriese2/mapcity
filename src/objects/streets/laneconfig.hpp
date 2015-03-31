#pragma once

#include <vector>
#include <set>

struct Lane;
enum class LANETYPE : std::uint8_t { CAR, PEDESTRIAN };

class LaneConfig {
	public:
		LaneConfig() {}
		LaneConfig(const std::vector<Lane> &);

		float getTotalWidth() const;
		std::vector<float> getLaneCenters() const;
	private:
		std::vector<Lane> m_lanes;
};

struct Lane {
	Lane(const std::set<LANETYPE> & t, float w, float s)
	  : types{t}, width{w}, speedlimit{s} {}
	std::set<LANETYPE> types;
	float width;
	float speedlimit;
};
