/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "ogl.h"
#include "stl.h"
#include "glm.h"

namespace ace {
	
class Camera {
private:

	// statics: global camera container
	static std::vector<Camera*> s_camContainer;
	static int s_nextId;

	// camera specific
	int  m_id;
	bool m_isPerspectiveCam;

	// 3D Camera
	glm::vec3 m_pos;
	glm::vec3 m_dir;
	glm::vec3 m_up;

	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 m_model;

	float m_fov;
	float m_near;
	float m_far;
	float m_aspectratio;

	void Lookat();
	void Perspective();

	// 2D Camera
	float m_left;
	float m_right;
	float m_bottom;
	float m_top;

	void Ortho();
public:
	Camera( glm::vec3& pos, glm::vec3& dir, glm::vec3& up, float fov,
			float aspect, float near, float far );
	Camera( float left, float right, float bottom, float top );
	~Camera();
	
	void update();
	
	void move( float v );
	void strafe( float dir );

	void setPos( glm::vec3& );
	void setDir( glm::vec3& );

	void rotateX( float angle );
	void rotateY( float angle );
	void rotateZ( float angle );

	void yaw( float angle );
	void pitch( float angle );
	void roll( float angle );

	glm::mat4& getProjectionMatrix();
	glm::mat4& getViewMatrix();
	glm::mat4& getModelMatrix();

	inline glm::vec3& getPos() { return m_pos; };
	inline glm::vec3& getDir() { return m_dir; };
	inline glm::vec3& getUp()  { return m_up; };

	static Camera* get( int id );
	static Camera* getActive();
	inline int getId() { return m_id; };
};

}

#endif // CAMERA_H