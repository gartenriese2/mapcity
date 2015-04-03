#include "car.hpp"

#include "../../rendering/conversion.hpp"

#include <glm/gtx/rotate_vector.hpp>

constexpr auto k_minSpeed = -20.f;
constexpr auto k_maxSpeed = 50.f;
constexpr auto k_friction = 0.5f;
constexpr auto k_stopSpeed = 2.f;

Car::Car(const glm::vec3 & pos, const glm::vec3 & dir, const std::string & color,
		const std::string & size)
  : Vehicle(pos, dir, color, size)
{
	m_drawables.back()->type = getType();
}

void Car::update(const float t) {
	LOG_ASSERT(t > 0.f, "NO NEGATIVE TIME STEPS!");
}

UDriveItCar::UDriveItCar(const glm::vec3 & pos, const glm::vec3 & dir,
		const std::unique_ptr<core::Input> & input, const std::string & color,
		const std::string & size)
  : Vehicle(pos, dir, color, size)
{
	initKeys(input);
	m_drawables.back()->type = getType();
}

void UDriveItCar::update(const float t) {
	LOG_ASSERT(t > 0.f, "NO NEGATIVE TIME STEPS!");
	const auto s = t * m_speed + 0.5f * m_acceleration * t * t;
	m_speed += m_acceleration * t;
	m_speed = std::min(std::max(m_speed, k_minSpeed), k_maxSpeed);
	// friction
	m_speed -= m_speed * k_friction * std::min(1.f / k_friction, t);
	if (std::abs(m_acceleration) <= 0.f && std::abs(m_speed) < k_stopSpeed) {
		m_speed = 0.f;
	}

	m_drawables[0]->object.move(gameToGraphics(s), m_dir);
	auto turnDiff = glm::sign(m_speed) * t * m_turnSpeed;
	if (std::abs(m_speed) <= 2.f) {
		turnDiff = 0.f;
	} else if (std::abs(m_speed) <= 8.f) {
		turnDiff *= std::sqrt(std::sqrt(std::sqrt(std::log2(std::abs(m_speed) / 2.f) / 2.f)));
	}
	m_dir = glm::rotateZ(m_dir, glm::radians(turnDiff));
	m_drawables[0]->object.rotate(glm::radians(turnDiff), {0.f, 0.f, 1.f});
}

void UDriveItCar::setTurnSpeed(const float speed) {
	m_turnSpeed = speed;
}

void UDriveItCar::setAcceleration(const float acc) {
	m_acceleration = acc;
}

void UDriveItCar::initKeys(const std::unique_ptr<core::Input> & input) {
	input->addKeyFunc([&](const int key, const int, const int action, const int){
		if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
			setAcceleration(30.f);
		}
		if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
			setAcceleration(0.f);
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
			setAcceleration(-45.f);
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
			setAcceleration(0.f);
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
			setTurnSpeed(75.f);
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
			setTurnSpeed(0.f);
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
			setTurnSpeed(-75.f);
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
			setTurnSpeed(0.f);
		}
	});
}
