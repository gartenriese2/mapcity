#include "camera.hpp"

#include "debug.hpp"

#include <utility>

Camera::Camera(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & up, float fov,
	unsigned int width, unsigned int height, float near)
  : m_width(width),
  	m_height(height),
  	m_fov(fov),
  	m_near(near),
  	m_pos(pos),
  	m_dir(glm::normalize(dir)),
  	m_up(glm::normalize(up)),
  	m_initPos(m_pos),
  	m_initDir(m_dir),
  	m_initUp(m_up)
{

	calculateView();
	calculateProj();

}

void Camera::resize(unsigned int width, unsigned int height) {

	if (width == 0) width = 1;
	if (height == 0) height = 1;

	m_width = width;
	m_height = height;

	calculateProj();

}

void Camera::calculateView() {

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);

}

void Camera::calculateProj() {

	m_proj = glm::infinitePerspective(m_fov, static_cast<float>(m_width) / static_cast<float>(m_height), m_near);

}

void Camera::reset() {

	m_pos = m_initPos;
	m_dir = m_initDir;
	m_up = m_initUp;

	calculateView();

}

void Camera::move(const glm::vec3 & change) {

	m_pos += change;

	calculateView();

}

void Camera::moveTo(const glm::vec3 & to) {

	m_pos = to;

	calculateView();

}

void Camera::rotate(float radians, const glm::vec3 & axis) {

	if (glm::length(axis) != 0.f) {

		glm::mat4 rot = glm::rotate(glm::mat4(1.f), radians, axis);
		glm::vec4 tmp = rot * glm::vec4(m_dir, 1.f);
		m_dir = glm::vec3(tmp[0], tmp[1], tmp[2]);
		tmp = rot * glm::vec4(m_up, 1.f);
		m_up = glm::vec3(tmp[0], tmp[1], tmp[2]);

		calculateView();

	}

}

void Camera::rotateAround(float radians, const glm::vec3 & axis, const glm::vec3 & point) {

	if (glm::length(axis) != 0.f) {

		rotate(radians, axis);

		// http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html -> Section 6.2
		float x = m_pos.x;
		float y = m_pos.y;
		float z = m_pos.z;
		float a = point.x;
		float b = point.y;
		float c = point.z;
		glm::vec3 nAxis = glm::normalize(axis);
		float u = nAxis.x;
		float v = nAxis.y;
		float w = nAxis.z;

		float retX = (a * (v*v + w*w) - u * (b*v + c*w - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ x * glm::cos(radians) + (-c*v + b*w - w*y + v*z) * glm::sin(radians);
		float retY = (b * (u*u + w*w) - v * (a*u + c*w - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ y * glm::cos(radians) + (c*u - a*w + w*x - u*z) * glm::sin(radians);
		float retZ = (c * (u*u + v*v) - w * (a*u + b*v - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ z * glm::cos(radians) + (-b*u + a*v - v*x + u*y) * glm::sin(radians);

		moveTo({retX, retY, retZ});

	}

}