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
	SPLINE,
	POLYGON
};

typedef std::vector<glm::vec3> vectorVec3;

class Object {
	
	public:
		
		Object();
		~Object();

		virtual void init();

		const glm::mat4 & getModelMatrix() const { return m_modelMatrix; }
		
		void draw() const;

	protected:

		GLuint m_vertexArray;

		GLuint m_vertexBuffer;
		GLuint m_normalBuffer;
		GLuint m_colorBuffer;
		GLuint m_indexBuffer;
		
		int m_triangles;
		glm::mat4 m_modelMatrix;

		virtual void initObject() {};
		void setTriangles(const int t) { m_triangles = t; }
		void setModelMatrix(const glm::mat4 mat) { m_modelMatrix = mat; }

		void fillBuffers(const unsigned long, const unsigned long, GLfloat * &, GLfloat * &, GLfloat * &, GLushort * &);
		void changeVertexBuffer(const unsigned long, GLfloat * &);

		void createCuboidData(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, GLfloat * &, GLfloat * &, GLushort * &);
		glm::vec3 drawHermite(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float);
		void addQuadToData(std::vector<GLfloat> &, std::vector<GLfloat> &, std::vector<GLushort> &, std::vector<GLfloat> &, 
							const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 &);
		void addQuadToData(std::vector<GLfloat> &, std::vector<GLfloat> &, std::vector<GLushort> &,	std::vector<GLfloat> &,
							const vectorVec3 &,	const glm::vec3 &);

};



#endif