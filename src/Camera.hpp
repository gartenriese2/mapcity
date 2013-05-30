#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm.h"

class Camera {
public:
	Camera() {};
	Camera(glm::vec3, glm::vec3, glm::vec3, float, float, float, float);

	inline glm::mat4 getViewMat() { return m_view; }
	inline glm::mat4 getProjMat() { return m_proj; }

	void move(float, float, float);
	
private:
	glm::mat4 m_view;
	glm::mat4 m_proj;

	glm::vec3 m_pos;
	glm::vec3 m_dir;
	glm::vec3 m_up;
};

#endif
