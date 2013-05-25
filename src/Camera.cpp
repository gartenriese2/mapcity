#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 look, glm::vec3 up, float fov, float ratio, float near, float far) {
	m_view = glm::lookAt(pos, pos + look, up);
	m_proj = glm::perspective(fov, ratio, near, far);
}