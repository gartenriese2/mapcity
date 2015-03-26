#include "path.hpp"

#include "../rendering/conversion.hpp"

constexpr auto k_width = 0.5f;

Path::Path(Manager & m)
  : Drawable{m}
{

}

StraightPath::StraightPath(Manager & m, const glm::vec3 & a, const glm::vec3 & b)
  : Path{m},
	m_a{a},
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
