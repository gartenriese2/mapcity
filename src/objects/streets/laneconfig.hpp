#pragma once

#include <vector>
#include <set>
#include <glm/glm.hpp>
#include <string>

struct Lane;
enum class LANETYPE : std::uint8_t { CAR, PEDESTRIAN };

class LaneConfig {
	public:
		LaneConfig() {}
		LaneConfig(const std::vector<std::string> &, const std::vector<bool> &);

		float getTotalWidth() const;
		std::vector<float> getLaneCenters() const;
		const std::vector<Lane> & getLanes() const;
		const std::vector<bool> & getDirections() const;
	private:
		std::vector<Lane> m_lanes;
		std::vector<bool> m_directions;
};

struct Lane {
	Lane(const std::set<LANETYPE> & t, float w, float s, const glm::vec3 & c)
	  : types{t}, width{w}, speedlimit{s}, color{c} {}
	bool allows(LANETYPE type) const { return types.count(type) != 0; }
	std::set<LANETYPE> types;
	float width;
	float speedlimit;
	glm::vec3 color;
};

inline bool operator==(const Lane & lhs, const Lane & rhs){
	return lhs.types == rhs.types && std::abs(lhs.width - rhs.width) <= 0.f
			&& std::abs(lhs.speedlimit - rhs.speedlimit) <= 0.f	&& lhs.color == rhs.color;
}
