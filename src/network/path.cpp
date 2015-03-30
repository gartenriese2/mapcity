#include "path.hpp"

#include "../rendering/conversion.hpp"

#include <MonoEngine/core/log.hpp>

constexpr auto k_width = 0.5f;

StraightPath::StraightPath(const glm::vec3 & a, const glm::vec3 & b)
  : m_a{a},
	m_b{b}
{
	m_a.z += 5.f;
	m_b.z += 5.f;
	initModelMatrix();
}

void StraightPath::initModelMatrix() {
	const auto scaling = gameToGraphics(glm::vec3{glm::length(m_b - m_a) * 0.5f, k_width * 0.5f, 0.f});
	m_object.scale(scaling);

	const auto angle = glm::atan((m_b - m_a).y, (m_b - m_a).x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo(gameToGraphics((m_a + m_b) * 0.5f));
}

glm::vec3 StraightPath::getPosition(const float pos) const {
	if (pos < 0.f) {
		LOG_WARNING("Trying to access Path outside its path");
		return m_a;
	}
	if (pos > 1.f) {
		LOG_WARNING("Trying to access Path outside its path");
		return m_b;
	}
	return (1.f - pos) * m_a + pos * m_b;
}

glm::vec3 StraightPath::getDirection(const float) const {
	return glm::normalize(m_b - m_a);
}

float StraightPath::advance(const glm::vec3 & pos, const float dist) const {
	if (!isOnPath(pos)) {
		LOG_WARNING("pos not on path");
		return -1.f;
	}
	const auto newPos = pos + dist * glm::normalize(m_b - m_a);
	return glm::length(newPos - m_a) / glm::length(m_b - m_a);
}

bool StraightPath::isOnPath(const glm::vec3 & pos) const {
	const auto pos2D = glm::vec2(pos.x, pos.y);
	const auto a2D = glm::vec2(m_a.x, m_a.y);
	const auto b2D = glm::vec2(m_b.x, m_b.y);
	if (pos2D == a2D || pos2D == b2D) {
		return true;
	}
	const auto posDir = pos2D - a2D;
	const auto pathDir = b2D - a2D;
	const auto dotProduct = glm::dot(glm::normalize(posDir), glm::normalize(pathDir));
	return dotProduct >= 0.999f && glm::length(posDir) <= glm::length(pathDir);
}
