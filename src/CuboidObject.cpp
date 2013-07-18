#include "CuboidObject.hpp"

CuboidObject::CuboidObject(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side, const float height, const glm::vec3 & color) {

	m_center = center;
	m_front = front;
	m_side = side;
	m_height = height;
	m_color = color;

	initObject();

}

CuboidObject::~CuboidObject() {

}

void CuboidObject::initObject() {

	GLfloat * vertexData;
	GLfloat * normalData;
	GLushort * indexData;

	glm::vec3 a = m_center + m_front + m_side;
	glm::vec3 b = m_center + m_front - m_side;
	glm::vec3 c = a + glm::vec3(0,1,0) * m_height;
	glm::vec3 d = m_center - m_front + m_side;

	createCuboidData(a, b, c, d, vertexData, normalData, indexData);

	GLfloat * colorData = new GLfloat[72];
	for (int i = 0; i < 72; i += 3) {
		colorData[i] = m_color[0];
		colorData[i + 1] = m_color[1];
		colorData[i + 2] = m_color[2];
	}

	fillBuffers(72, 36, vertexData, normalData, colorData, indexData);
	delete [] vertexData;
	delete [] normalData;
	delete [] colorData;
	delete [] indexData;

	setTriangles(12);

}