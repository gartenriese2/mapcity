#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 look, glm::vec3 up, float fov, float ratio, float near, float far) {
	
	m_pos = pos;
	m_dir = look;
	m_up = up;

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);
	m_proj = glm::perspective(fov, ratio, near, far);
}

void Camera::move(float forward, float sideward, float upward) {

	glm::vec3 side = glm::normalize(glm::cross(m_dir, m_up));
	m_pos += forward * m_dir + sideward * side + upward * m_up;

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);

}