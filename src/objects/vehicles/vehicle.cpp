#include "vehicle.hpp"

#include "../../rendering/conversion.hpp"

#include <MonoEngine/core/log.hpp>
#include <glm/gtx/rotate_vector.hpp>

const auto k_dimension = glm::vec3{4.7f, 1.83f, 1.43f};

Vehicle::Vehicle(const glm::vec3 & pos, const glm::vec3 & dir)
  : m_pos{pos},
	m_dir{dir}
{
	LOG_ASSERT(std::abs(pos.z) <= 0.f, "VEHICLE NOT AT GROUND LEVEL!");
	LOG_ASSERT(std::abs(glm::length(dir)) > 0.f, "DIRECTION OF VEHICLE IS ZERO!");
	m_dir = glm::normalize(m_dir);
	initModelMatrix();
}

void Vehicle::initModelMatrix() {
	const auto scaling = gameToGraphics(k_dimension * 0.5f);
	m_object.scale(scaling);

	const auto angle = glm::atan(m_dir.y, m_dir.x);
	m_object.rotate(angle, {0.f, 0.f, 1.f});

	m_object.moveTo(gameToGraphics(m_pos + glm::vec3{0.f, k_dimension.y * 0.5f, 0.f}));
}

void Vehicle::update(const float step) {

	const auto diff = step * m_speed;
	m_object.move(gameToGraphics(diff), m_dir);
}

void Vehicle::setSpeed(const float speed) {
	m_speed = speed;
}

void Vehicle::turn(const float angle) {
	m_dir = glm::rotateZ(m_dir, glm::radians(angle));
	m_object.rotate(glm::radians(angle), {0.f, 0.f, 1.f});
}
