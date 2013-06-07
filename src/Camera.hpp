#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm.h"
#include <iostream>
#include <math.h>

class Camera {
public:
	Camera() {};
	Camera(glm::vec3, glm::vec3, glm::vec3, float, int, int, float, float);

	inline glm::mat4 getViewMat() { return m_view; }
	inline glm::mat4 getProjMat() { return m_proj; }

	void reset();
	void move(float, float, float);
	void rotate(float, float);
	void rotateAround(float);
	void zoom(int);
	
private:
	
	int m_width;
	int m_height;

	float m_fov;

	glm::mat4 m_view;
	glm::mat4 m_proj;

	glm::vec3 m_pos;
	glm::vec3 m_dir;
	glm::vec3 m_up;

	glm::vec3 m_initPos;
	glm::vec3 m_initDir;
	glm::vec3 m_initUp;
};

#endif
