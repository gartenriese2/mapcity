#include "intersection.hpp"

#include "../../rendering/conversion.hpp"

#include <glm/gtc/constants.hpp>

Intersection::Intersection(const std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>> & streets)
{
	// TO DO: different Z?
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

	const auto & config1 = m_streets.front()->getConfig();
	const auto & config2 = m_streets.back()->getConfig();

	const auto & dir1 = config1.getDirections();
	const auto & dir2 = config2.getDirections();
	const auto & lanes1 = config1.getLanes();
	const auto & lanes2 = config2.getLanes();

	if (dir1 == dir2) {
		// same directions and lane numbers
		for (auto i = 0u; i < lanes1.size(); ++i) {
			if (std::abs(lanes1[i].width - lanes2[i].width) > 0.f) {
				LOG_ERROR("trying to connect streets with different lane widths!");
			}
		}

		const auto dira = glm::vec2(m_tangents.front().x, m_tangents.front().y);
		const auto dirb = -glm::vec2(m_tangents.back().x, m_tangents.back().y);
		if (dira != dirb) {
			// angle -> curve
			const auto anglea = glm::atan(dira.y, dira.x);
			const auto angleb = glm::atan(dirb.y, dirb.x);
			auto angle = angleb - anglea;
			// clamp between -PI and +PI
			if (angle < -glm::pi<float>()) angle += 2.f * glm::pi<float>();
			if (angle > glm::pi<float>()) angle -= 2.f * glm::pi<float>();

			const auto w = config1.getTotalWidth();
			const auto n1 = glm::normalize(glm::vec3(m_tangents.front().y, -m_tangents.front().x, 0.f));
			const auto n2 = glm::normalize(glm::vec3(m_tangents.back().y, -m_tangents.back().x, 0.f));
			const auto heightOffset = glm::vec3(0.f, 0.f, 0.03f);
			const auto x = glm::tan(std::abs(angle) * 0.5f) * 0.5f * w;
			const auto rotateRadians = angle >= 0.f ? anglea - glm::half_pi<float>() : angleb + glm::half_pi<float>();
			const auto tangentOffset = -glm::normalize(angle >= 0.f ? m_tangents.front() : m_tangents.back()) * x;
			const auto centerOffset = (angle >= 0.f ? n1 : n2) * 0.5f * w;
			const auto moveToPos = gameToGraphics(m_pos - centerOffset + heightOffset + tangentOffset);

			auto addFan = [&](const glm::vec4 & color, const float scaling){
				auto drawable = std::make_shared<Drawable>();
				drawable->type = "IntersectionInner";
				drawable->color = color;
				drawable->renderType = RenderTypeName::FAN;
				drawable->misc = glm::vec4(std::abs(glm::degrees(angle)), 0.f, 0.f, 0.f);
				drawable->dynamic = false;
				drawable->unicolored = false;
				drawable->object.scale({scaling, scaling, 1.f});
				drawable->object.rotate(rotateRadians, {0.f, 0.f, 1.f});
				drawable->object.moveTo(moveToPos);
				m_drawables.emplace_back(drawable);
			};

			auto addAnnulus = [&](const glm::vec4 & color, const float relInner, const float scaling){
				auto drawable = std::make_shared<Drawable>();
				drawable->type = "IntersectionOuter";
				drawable->color = color;
				drawable->renderType = RenderTypeName::ANNULUS;
				drawable->misc = glm::vec4(std::abs(glm::degrees(angle)), relInner, relInner, 1.f);
				drawable->dynamic = false;
				drawable->unicolored = false;
				drawable->object.scale({scaling, scaling, 1.f});
				drawable->object.rotate(rotateRadians, {0.f, 0.f, 1.f});
				drawable->object.moveTo(moveToPos);
				m_drawables.emplace_back(drawable);
			};

			auto _w = lanes1[0].width;
			addFan(glm::vec4(lanes1[0].color, 1.f), gameToGraphics(_w));
			for (auto i = 1u; i < lanes1.size(); ++i) {
				const auto _w_old = _w;
				_w += lanes1[i].width;
				addAnnulus(glm::vec4(lanes1[i].color, 1.f), _w_old / _w, gameToGraphics(_w));
			}

			// cut back streets
			if (glm::vec2(m_pos.x, m_pos.y) == m_streets.front()->getStartXY()) {
				m_streets.front()->moveStart(x);
			} else {
				m_streets.front()->moveEnd(-x);
			}
			if (glm::vec2(m_pos.x, m_pos.y) == m_streets.back()->getStartXY()) {
				m_streets.back()->moveStart(x);
			} else {
				m_streets.back()->moveEnd(-x);
			}

		}

	} else {
		// TO DO: no uniform connections
	}

	// TO DO: connect paths with a node
}
