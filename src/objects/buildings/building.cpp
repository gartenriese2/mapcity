#include "building.hpp"

#include "../../rendering/conversion.hpp"

#include <MonoEngine/core/log.hpp>

Building::Building(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
		const float height)
  : m_a{a},
	m_b{b},
	m_c{c},
	m_height{height}
{
	const bool as = glm::normalize(glm::cross(b - a, c - a)) == glm::vec3(0,0,1);
	LOG_ASSERT(as, "NO RIGHT ANGLE");
	initModelMatrix();
}

void Building::initModelMatrix() {
	const auto scaling = glm::vec3{gameToGraphics(glm::length(m_b - m_a) * 0.5f),
			gameToGraphics(glm::length(m_c - m_a) * 0.5f),
			gameToGraphics(m_height * 0.5f)};
	m_object.scale(scaling);
	const float angle = glm::atan((m_b - m_a).y, (m_b - m_a).x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});
	m_object.moveTo(gameToGraphics(0.5f * (m_b + m_c + glm::vec3(0.f, 0.f, m_height))));
}

ResidentialBuilding::ResidentialBuilding(const glm::vec3 & a, const glm::vec3 & b,
		const glm::vec3 & c, const float height)
  : Building(a, b, c, height)
{
}

OfficeBuilding::OfficeBuilding(const glm::vec3 & a, const glm::vec3 & b,
		const glm::vec3 & c, const float height)
  : Building(a, b, c, height)
{
}
