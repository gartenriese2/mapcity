#include "vehicle.hpp"

#include "../../rendering/conversion.hpp"

#include <MonoEngine/core/log.hpp>

#include <map>
#include <random>
#include "../../../resources/cars.db"

std::random_device rd;
std::mt19937 gen(rd());

Vehicle::Vehicle(const glm::vec3 & pos, const glm::vec3 & dir, const std::string & size,
		const std::string & color)
  : m_pos{pos},
	m_dir{dir}
{
	LOG_ASSERT(std::abs(pos.z) <= 0.f, "VEHICLE NOT AT GROUND LEVEL!");
	LOG_ASSERT(std::abs(glm::length(dir)) > 0.f, "DIRECTION OF VEHICLE IS ZERO!");
	m_dir = glm::normalize(m_dir);

	initColor(color);
	initSize(size);
	initModelMatrix();
}

void Vehicle::initModelMatrix() {
	const auto scaling = gameToGraphics(m_size * 0.5f);
	m_object.scale(scaling);

	const auto angle = glm::atan(m_dir.y, m_dir.x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo(gameToGraphics(m_pos + glm::vec3(0.f, 0.f, m_size.z)));
}

void Vehicle::initColor(const std::string & color) {
	if (color == "" || k_carColors.count(color) == 0) {
		// random
		std::uniform_int_distribution<> dis(0, static_cast<int>(k_carColors.size()) - 1);
		auto it = k_carColors.begin();
		std::advance(it, dis(gen));
		m_color = it->second;
	} else {
		m_color = k_carColors.at(color);
	}
}

void Vehicle::initSize(const std::string & size) {
	if (size == "" || k_carSizes.count(size) == 0) {
		// random
		std::uniform_int_distribution<> dis(0, static_cast<int>(k_carSizes.size()) - 1);
		auto it = k_carSizes.begin();
		std::advance(it, dis(gen));
		m_size = it->second;
	} else {
		m_size = k_carSizes.at(size);
	}
}
