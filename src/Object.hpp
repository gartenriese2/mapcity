#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "ogl.h"
#include "glm.h"
#include <iostream>
#include <vector>

enum class ObjectType {
	TRIANGLE,
	QUAD,
	HEXAGON,
	CUBOID,
	SPLINE
};

class Object {
public:
	
	Object();
	Object(ObjectType, const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3);
	Object(ObjectType, const glm::vec3, const glm::vec3, const float, const glm::vec3);
	Object(ObjectType, const glm::vec3, const glm::vec3, const float, const float, const glm::vec3);
	Object(ObjectType, const glm::vec3, const glm::vec3, const glm::vec3);
	Object(ObjectType, const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3);
	Object(ObjectType, const glm::vec3, const glm::vec3, const glm::vec3, const float, const glm::vec3);
	Object(ObjectType, std::vector<glm::vec3>, const float, const glm::vec3);
	~Object();

	unsigned long getID() const { return m_ID; }

	void init();

	glm::mat4 getModelMatrix() { return m_modelMatrix; }
	void setTriangles(int t) { m_triangles = t; }

	void fillBuffers(int, int, GLfloat * &, GLfloat * &, GLfloat * &, GLushort * &);
	void draw();

private:
	
	unsigned long m_ID;

	GLuint m_vertexArray;

	GLuint m_vertexBuffer;
	GLuint m_normalBuffer;
	GLuint m_colorBuffer;
	GLuint m_indexBuffer;
	
	int m_triangles;
	glm::mat4 m_modelMatrix;

	void setAsTriangle(const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void setAsQuad(const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void setAsQuad(const glm::vec3, const glm::vec3, const float, const glm::vec3 col = glm::vec3(1,1,1));
	void setAsQuad(const glm::vec3, const glm::vec3, const float, const float, const glm::vec3 col = glm::vec3(1,1,1));
	void setAsHexagon(const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void setAsCuboid(const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void setAsCuboid(const glm::vec3, const glm::vec3, const glm::vec3, const float, const glm::vec3 col = glm::vec3(1,1,1));
	void setAsSpline(std::vector<glm::vec3>, const float, const glm::vec3 col = glm::vec3(1,1,1));

	void createCuboidData(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, GLfloat * &, GLfloat * &, GLushort * &);
	glm::vec3 drawHermite(glm::vec3, glm::vec3, glm::vec3, glm::vec3, float);

};



#endif