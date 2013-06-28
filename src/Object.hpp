#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "ogl.h"
#include "glm.h"
#include <iostream>

class Object {
public:
	
	Object();
	~Object();

	inline glm::mat4 getModelMatrix() { return m_modelMatrix; }
	inline void setTriangles(int t) { m_triangles = t; }

	void fillBuffers(int, int, GLfloat * &, GLfloat * &, GLfloat * &, GLushort * &);
	void draw();

private:
	
	int m_ID;

	GLuint m_vertexArray;

	GLuint m_vertexBuffer;
	GLuint m_normalBuffer;
	GLuint m_colorBuffer;
	GLuint m_indexBuffer;
	
	int m_triangles;
	glm::mat4 m_modelMatrix;

};



#endif