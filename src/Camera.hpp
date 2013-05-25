#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm.h"

class Camera {
public:
	Camera(glm::vec3, glm::vec3, glm::vec3, float, float, float, float);
	
private:
	glm::mat4 m_view;
	glm::mat4 m_proj;
};

#endif
