#include "light.hpp"

Light::Light(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & color) {
	
	m_lightData.bools = {1.f, 0.f, 0.f, 0.f};
	m_lightData.position = glm::vec4(pos, 1.f);
	m_lightData.color = glm::vec4(color, 1.f);
	m_lightData.ambient = m_lightData.color * 0.2f;
	m_lightData.direction = glm::vec4(dir, 1.f);
	m_lightData.attenuation = {0.05f, 0.02f, 0.002f, 0.f};
	m_lightData.spot = {0.5f, 10.f, 0.f, 0.f};

}

void Light::rotate(float radians, const glm::vec3 & axis) {

	if (glm::length(axis) != 0.f) {

		glm::mat4 rot = glm::rotate(glm::mat4(1.f), radians, axis);
		m_lightData.direction = rot * m_lightData.direction;

	}

}