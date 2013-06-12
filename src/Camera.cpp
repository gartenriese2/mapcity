#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 look, glm::vec3 up, float fov, int width, int height, float near, float far) {
	
	m_width = width;
	m_height = height;

	m_pos = pos;
	m_dir = glm::normalize(look);
	m_up = glm::normalize(up);

	m_fov = fov;

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);
	m_proj = glm::perspective(fov, static_cast<float>(width) / static_cast<float>(height), near, far);

	m_initPos = m_pos;
	m_initDir = m_dir;
	m_initUp = m_up;

}

Camera::Camera(glm::vec3 pos, glm::vec3 look, glm::vec3 up, float left, float right, float top, float bottom) {

	m_pos = pos;
	m_dir = glm::normalize(look);
	m_up = glm::normalize(up);

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);
	m_proj = glm::ortho(left, right, bottom, top);

	m_initPos = m_pos;
	m_initDir = m_dir;
	m_initUp = m_up;

}

void Camera::reset() {

	m_pos = m_initPos;
	m_dir = m_initDir;
	m_up = m_initUp;
	m_view = glm::lookAt(m_initPos, m_initPos + m_initDir, m_initUp);
	
}

void Camera::move(float forward, float sideward, float upward) {
	
	forward *= glm::sqrt(m_pos.y / 10.f);
	sideward *= glm::sqrt(m_pos.y / 10.f);
	upward *= glm::sqrt(m_pos.y / 10.f);
	if (m_pos.y <= 1.0 && upward > 0.f) upward = 0.f;

	glm::vec3 up(forward * m_dir.x, 0, forward * m_dir.z);
	glm::vec3 right(-sideward * m_dir.z, 0, sideward * m_dir.x);
	glm::vec3 lift(0, upward * m_dir.y, 0);

	m_pos += up + right + lift;

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);

}

void Camera::zoom(int zoom) {
	
	if (m_pos.y > 10.f || zoom < 0) {
		float factor = glm::pow(m_pos.y, 0.75f);

		m_pos += static_cast<float>(zoom) * factor * m_dir;
		m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);
	}
}

void Camera::rotate(float dx, float dy) {
	
	float radX = -m_fov * M_PI / 180.f * dx / static_cast<float>(m_width);
	float radY = -m_fov * M_PI / 180.f * dy / static_cast<float>(m_width);

	glm::mat4 umat(1.f);
	m_dir = glm::vec3(glm::rotate(umat, radX, m_up) * glm::vec4(m_dir, 1.f));

	glm::vec3 right_dir = glm::normalize(glm::cross(m_dir, m_up));

	m_dir = glm::vec3(glm::rotate(umat, radY, right_dir) * glm::vec4(m_dir, 1.f));
	m_dir = glm::normalize(m_dir);
	m_up = glm::normalize(glm::cross(right_dir, m_dir));

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);

}

void Camera::rotateAround(float angle) {

	float steps = m_pos.y / -m_dir.y;
	glm::vec3 center = m_pos + m_dir * steps;

	glm::mat4 umat(1.f);
	float rad = angle * M_PI / 180.f;
	m_dir = glm::vec3(glm::rotate(umat, rad, glm::vec3(0.f,1.f,0.f)) * glm::vec4(m_dir, 1.f));
	m_pos = center - m_dir * steps;
	m_up = glm::vec3(glm::rotate(umat, rad, glm::vec3(0.f,1.f,0.f)) * glm::vec4(m_up, 1.f));

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);

}