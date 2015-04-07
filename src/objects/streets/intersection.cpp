#include "intersection.hpp"

#include "../../rendering/conversion.hpp"

Intersection::Intersection(const std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>> & streets)
{
	LOG_ASSERT(streets.first->getStart() == streets.second->getStart()
			|| streets.first->getEnd() == streets.second->getStart()
			|| streets.first->getStart() == streets.second->getEnd()
			|| streets.first->getEnd() == streets.second->getEnd(),
			"streets do not touch");
	m_streets.emplace_back(streets.first);
	m_streets.emplace_back(streets.second);
	if (streets.first->getStart() == streets.second->getStart()
		|| streets.first->getStart() == streets.second->getEnd()) {
		m_pos = streets.first->getStart();
		m_tangents.emplace_back(m_streets.front()->getStartTangent());
	} else {
		m_pos = streets.first->getEnd();
		m_tangents.emplace_back(m_streets.front()->getEndTangent());
	}
	if (m_pos == m_streets.back()->getStart()) {
		m_tangents.emplace_back(m_streets.back()->getStartTangent());
	} else {
		m_tangents.emplace_back(m_streets.back()->getEndTangent());
	}

	const auto & dir1 = streets.first->getConfig().getDirections();
	const auto & dir2 = streets.second->getConfig().getDirections();
	const auto & lanes1 = streets.first->getConfig().getLanes();
	const auto & lanes2 = streets.second->getConfig().getLanes();
	// const auto & centers1 = streets.first->getConfig().getLaneCenters();
	// const auto & centers2 = streets.second->getConfig().getLaneCenters();
	if (lanes1 == lanes2) {
		// same config -> no visible change!
		// TO DO: connect paths with a node
	} else if (dir1 == dir2) {
		// same directions and lane numbers
		const auto dira = glm::vec2(m_tangents.front().x, m_tangents.front().y);
		const auto dirb = -glm::vec2(m_tangents.back().x, m_tangents.back().y);
		const auto angle = glm::atan(dirb.y, dirb.x) - glm::atan(dira.y, dira.x);
		const auto anglea = glm::atan(dira.y, dira.x);
		const auto angleb = glm::atan(dirb.y, dirb.x);
		for (auto i = 0u; i < dir1.size(); ++i) {
			if (lanes1[i].types == lanes2[i].types) {
				// same types allowed
				// const auto laneWidth1 = lanes1[i].width;
				// const auto laneWidth2 = lanes2[i].width;
				// const auto laneCenter1 = centers1[i];
				// const auto laneCenter2 = centers2[i];
				// const auto n1 = glm::vec3(m_tangents.front().y, -m_tangents.front().x, 0.f);
				// const auto n2 = glm::vec3(m_tangents.back().y, -m_tangents.back().x, 0.f);
				// const auto side1a = m_pos - n1 * m_streets.front()->getConfig().getTotalWidth() * 0.5f;
				// const auto side1b = m_pos + n1 * m_streets.front()->getConfig().getTotalWidth() * 0.5f;
				// const auto side2a = m_pos - n2 * m_streets.front()->getConfig().getTotalWidth() * 0.5f;
				// const auto side2b = m_pos + n2 * m_streets.front()->getConfig().getTotalWidth() * 0.5f;
				// const auto a = side1a - m_tangents.front() + (laneCenter1 - laneWidth1 * 0.5f) * n1;
				// const auto b = side1b - m_tangents.front() + (laneCenter1 - laneWidth1 * 0.5f) * n1;
			}
		}
		m_drawables.emplace_back(std::make_shared<Drawable>());
		auto & drawable = m_drawables.back();
		drawable->type = "Intersection";
		drawable->color = glm::vec4(0.f);
		drawable->renderType = RenderTypeName::ANNULUS;
		drawable->misc = glm::vec4(std::abs(glm::degrees(angle)), 0.5f, 0.f, 0.f);
		drawable->dynamic = false;
		drawable->unicolored = false;
		const auto scaling = gameToGraphics(m_streets.front()->getConfig().getTotalWidth() * 0.5f);
		drawable->object.scale({scaling, scaling, 1.f});
		if (angle >= 0.f) {
			drawable->object.rotate(anglea - glm::radians(90.f), {0.f, 0.f, 1.f});
		} else {
			drawable->object.rotate(angleb + glm::radians(90.f), {0.f, 0.f, 1.f});
		}
		drawable->object.moveTo(gameToGraphics(m_pos + glm::vec3(0.f, 0.f, 0.05f)));
	}
}
