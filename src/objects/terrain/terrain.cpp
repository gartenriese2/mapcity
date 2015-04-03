#include "terrain.hpp"

#include "../../rendering/conversion.hpp"

Terrain::Terrain(const glm::vec3 & start, const glm::vec3 & end)
  : m_start{start},
	m_end{end}
{
	initDrawables();
}


void Terrain::initDrawables() {
	m_drawables.emplace_back(std::make_shared<Drawable>());
	m_drawables.back()->type = getType();
	m_drawables.back()->color = glm::vec4{0.5f, 1.f, 0.5f, 1.f};
	m_drawables.back()->renderType = RenderTypeName::QUAD;
	m_drawables.back()->dynamic = false;
	m_drawables.back()->unicolored = true;
	const auto scaling = gameToGraphics(glm::vec2((m_end.x - m_start.x) * 0.5f,
			(m_end.y - m_start.y) * 0.5f));
	m_drawables.back()->object.scale({scaling.x, scaling.y, 1.f});
	m_drawables.back()->object.moveTo(gameToGraphics(m_start + m_end) * 0.5f);
}
