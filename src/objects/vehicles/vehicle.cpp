#include "vehicle.hpp"

#include "../../rendering/conversion.hpp"

#include <MonoEngine/core/log.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <map>
#include <random>
#include "../../../resources/cars.db"

constexpr auto k_minSpeed = -20.f;
constexpr auto k_maxSpeed = 50.f;
constexpr auto k_friction = 0.5f;
constexpr auto k_stopSpeed = 2.f;
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

UDriveItVehicle::UDriveItVehicle(const glm::vec3 & pos, const glm::vec3 & dir,
		const std::unique_ptr<core::Input> & input, const std::string & color,
		const std::string & size)
  : Vehicle(pos, dir, color, size)
{
	initKeys(input);
}

void UDriveItVehicle::update(const float t) {
	LOG_ASSERT(t > 0.f, "NO NEGATIVE TIME STEPS!");
	const auto s = t * m_speed + 0.5f * m_acceleration * t * t;
	m_speed += m_acceleration * t;
	m_speed = std::min(std::max(m_speed, k_minSpeed), k_maxSpeed);
	// friction
	m_speed -= m_speed * k_friction * std::min(1.f / k_friction, t);
	if (std::abs(m_acceleration) <= 0.f && std::abs(m_speed) < k_stopSpeed) {
		m_speed = 0.f;
	}

	m_object.move(gameToGraphics(s), m_dir);
	const auto turnDiff = m_speed * t * m_turnSpeed;
	m_dir = glm::rotateZ(m_dir, glm::radians(turnDiff));
	m_object.rotate(glm::radians(turnDiff), {0.f, 0.f, 1.f});
}

void UDriveItVehicle::setTurnSpeed(const float speed) {
	m_turnSpeed = speed;
}

void UDriveItVehicle::setAcceleration(const float acc) {
	m_acceleration = acc;
}

void UDriveItVehicle::initKeys(const std::unique_ptr<core::Input> & input) {
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
			setTurnSpeed(5.f);
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
			setTurnSpeed(0.f);
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
			setTurnSpeed(-5.f);
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
			setTurnSpeed(0.f);
		}
	});
}
