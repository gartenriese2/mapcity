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
		Object(const ObjectType &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		Object(const ObjectType &, const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 &);
		Object(const ObjectType &, const glm::vec3 &, const glm::vec3 &, const float, const float, const glm::vec3 &);
		Object(const ObjectType &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		Object(const ObjectType &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		Object(const ObjectType &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 &);
		Object(const ObjectType &, const vectorVec3 &, const float, const glm::vec3 &);
		Object(const ObjectType &, const vectorVec3 &, const glm::vec3 &, const glm::vec3 &);
		~Object();

		unsigned long getID() const { return m_ID; }

		void init();

		const glm::mat4 & getModelMatrix() const { return m_modelMatrix; }
		void setTriangles(const int t) { m_triangles = t; }

		void fillBuffers(const int, const int, GLfloat * &, GLfloat * &, GLfloat * &, GLushort * &);
		void draw() const;

	private:
		
		unsigned long m_ID;

		GLuint m_vertexArray;

		GLuint m_vertexBuffer;
		GLuint m_normalBuffer;
		GLuint m_colorBuffer;
		GLuint m_indexBuffer;
		
		int m_triangles;
		glm::mat4 m_modelMatrix;

		void setAsTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsQuad(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsQuad(const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsQuad(const glm::vec3 &, const glm::vec3 &, const float, const float, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsHexagon(const glm::vec3 &, const glm::vec3 &, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsCuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsCuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsSpline(const vectorVec3 &, const float, const glm::vec3 & col = glm::vec3(1,1,1));
		void setAsPolygon(const vectorVec3 &, const glm::vec3 &, const glm::vec3 & col = glm::vec3(1,1,1));

		void createCuboidData(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, GLfloat * &, GLfloat * &, GLushort * &);
		glm::vec3 drawHermite(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float);
		void addQuadToData(std::vector<GLfloat> &, std::vector<GLfloat> &, std::vector<GLushort> &, std::vector<GLfloat> &, 
							const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 &);

};



#endif