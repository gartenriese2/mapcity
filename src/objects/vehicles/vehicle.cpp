#include "vehicle.hpp"

#include "../../rendering/conversion.hpp"

#include <MonoEngine/core/log.hpp>
#include <glm/gtx/rotate_vector.hpp>

const auto k_dimension = glm::vec3{4.7f, 1.83f, 1.43f};
constexpr auto k_minSpeed = -20.f;
constexpr auto k_maxSpeed = 50.f;

Vehicle::Vehicle(Manager & m, const glm::vec3 & pos, const glm::vec3 & dir)
  : Drawable{m},
	m_pos{pos},
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

void Vehicle::update(const float t) {
	const auto s = t * m_speed + 0.5f * m_acceleration * t * t;
	m_speed += m_acceleration * t;
	m_speed = std::min(std::max(m_speed, k_minSpeed), k_maxSpeed);
	// friction
	m_speed -= m_speed * 0.5f * t;

	m_object.move(gameToGraphics(s), m_dir);
	const auto turnDiff = m_speed * t * m_turnSpeed;
	m_dir = glm::rotateZ(m_dir, glm::radians(turnDiff));
	m_object.rotate(glm::radians(turnDiff), {0.f, 0.f, 1.f});
}

void Vehicle::setTurnSpeed(const float speed) {
	m_turnSpeed = speed;
}

void Vehicle::setAcceleration(const float acc) {
	m_acceleration = acc;
}
