#include "intersection.hpp"

#include "../../rendering/conversion.hpp"

Intersection::Intersection(const std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>> & streets)
{
	LOG_ASSERT(streets.first->getStartXY() == streets.second->getStartXY()
			|| streets.first->getEndXY() == streets.second->getStartXY()
			|| streets.first->getStartXY() == streets.second->getEndXY()
			|| streets.first->getEndXY() == streets.second->getEndXY(),
			"streets do not touch");
	m_streets.emplace_back(streets.first);
	m_streets.emplace_back(streets.second);
	if (streets.first->getStartXY() == streets.second->getStartXY()
		|| streets.first->getStartXY() == streets.second->getEndXY()) {
		m_pos = streets.first->getStart();
		m_tangents.emplace_back(m_streets.front()->getStartTangent());
	} else {
		m_pos = streets.first->getEnd();
		m_tangents.emplace_back(m_streets.front()->getEndTangent());
	}
	if (glm::vec2(m_pos.x, m_pos.y) == m_streets.back()->getStartXY()) {
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
		auto angle = glm::atan(dirb.y, dirb.x) - glm::atan(dira.y, dira.x);
		// if (angle < glm::radians(-180.f)) angle += glm::radians(180.f);
		// if (angle > glm::radians(180.f)) angle -= glm::radians(180.f);
		LOG(glm::degrees(angle));
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
		const auto totalwidth1 = m_streets.front()->getConfig().getTotalWidth();
		const auto n1 = glm::normalize(glm::vec3(m_tangents.front().y, -m_tangents.front().x, 0.f));
		const auto n2 = glm::vec3(m_tangents.back().y, -m_tangents.back().x, 0.f);
		const auto heightOffset = glm::vec3(0.f, 0.f, 0.03f);

		m_drawables.emplace_back(std::make_shared<Drawable>());
		auto & drawable = m_drawables.back();
		drawable->type = "Intersection";
		drawable->color = glm::vec4(1.f, 0.f, 1.f, 1.f);
		drawable->renderType = RenderTypeName::ANNULUS;
		drawable->misc = glm::vec4(std::abs(glm::degrees(angle)), (lanes1[0].width + lanes1[1].width) / totalwidth1, 0.f, 0.f);
		drawable->dynamic = false;
		drawable->unicolored = false;
		const auto scaling = gameToGraphics(totalwidth1);
		drawable->object.scale({scaling, scaling, 1.f});
		if (angle >= 0.f) {
			drawable->object.rotate(anglea - glm::radians(90.f), {0.f, 0.f, 1.f});
			const auto x = glm::tan(angle * 0.5f) * 0.5f * totalwidth1;
			const auto tangentOffset = -glm::normalize(m_tangents.front()) * x;
			const auto centerOffset = glm::vec3(n1.x, n1.y, 0.f) * 0.5f * totalwidth1;
			drawable->object.moveTo(gameToGraphics(m_pos - centerOffset + heightOffset + tangentOffset));
		} else {
			drawable->object.rotate(angleb + glm::radians(90.f), {0.f, 0.f, 1.f});
			const auto x = glm::tan(-angle * 0.5f) * 0.5f * totalwidth1;
			const auto tangentOffset = -glm::normalize(m_tangents.back()) * x;
			const auto centerOffset = glm::vec3(n2.x, n2.y, 0.f) * 0.5f * totalwidth1;
			drawable->object.moveTo(gameToGraphics(m_pos - centerOffset + heightOffset + tangentOffset));
		}


		m_drawables.emplace_back(std::make_shared<Drawable>());
		auto & drawable2 = m_drawables.back();
		drawable2->type = "Intersection";
		drawable2->color = glm::vec4(0.f);
		drawable2->renderType = RenderTypeName::FAN;
		drawable2->misc = glm::vec4(std::abs(glm::degrees(angle)), 0.f, 0.f, 0.f);
		drawable2->dynamic = false;
		drawable2->unicolored = false;
		const auto scaling2 = gameToGraphics(lanes1[0].width);
		drawable2->object.scale({scaling2, scaling2, 1.f});
		if (angle >= 0.f) {
			drawable2->object.rotate(anglea - glm::radians(90.f), {0.f, 0.f, 1.f});
			const auto x = glm::tan(angle * 0.5f) * 0.5f * totalwidth1;
			const auto tangentOffset = -glm::normalize(m_tangents.front()) * x;
			const auto centerOffset = glm::vec3(n1.x, n1.y, 0.f) * 0.5f * totalwidth1;
			drawable2->object.moveTo(gameToGraphics(m_pos - centerOffset + heightOffset + tangentOffset));
		} else {
			drawable2->object.rotate(angleb + glm::radians(90.f), {0.f, 0.f, 1.f});
			const auto x = glm::tan(-angle * 0.5f) * 0.5f * totalwidth1;
			const auto tangentOffset = -glm::normalize(m_tangents.back()) * x;
			const auto centerOffset = glm::vec3(n2.x, n2.y, 0.f) * 0.5f * totalwidth1;
			drawable2->object.moveTo(gameToGraphics(m_pos - centerOffset + heightOffset + tangentOffset));
		}

	}
}
