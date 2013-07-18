#include "CuboidObject.hpp"

CuboidObject::CuboidObject(const glm::vec3 & center, const glm::vec3 & front, const glm::vec3 & side, const float height, const glm::vec3 & color) {

	assert (height >= 0.f);

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

void CuboidObject::changeHeight(const float height) {

	assert (height >= 0.f);
	m_height = height;

	GLfloat * vertexData = new GLfloat[72];

	glm::vec3 a = m_center + m_front + m_side;
	glm::vec3 b = m_center + m_front - m_side;
	glm::vec3 c = a + glm::vec3(0,1,0) * m_height;
	glm::vec3 d = m_center - m_front + m_side;
	glm::vec3 e = c + (b - a);
	glm::vec3 f = d + (c - a);
	glm::vec3 g = e + (d - a);
	glm::vec3 h = g + (a - c);

	for (unsigned long i = 0; i < 3; i++) {
		
		vertexData[i + 0] = a[i];
		vertexData[i + 3] = b[i];
		vertexData[i + 6] = e[i];
		vertexData[i + 9] = c[i];

		vertexData[i + 12] = a[i];
		vertexData[i + 15] = c[i];
		vertexData[i + 18] = f[i];
		vertexData[i + 21] = d[i];

		vertexData[i + 24] = c[i];
		vertexData[i + 27] = e[i];
		vertexData[i + 30] = g[i];
		vertexData[i + 33] = f[i];

		vertexData[i + 36] = a[i];
		vertexData[i + 39] = d[i];
		vertexData[i + 42] = h[i];
		vertexData[i + 45] = b[i];
		
		vertexData[i + 48] = e[i];
		vertexData[i + 51] = b[i];
		vertexData[i + 54] = h[i];
		vertexData[i + 57] = g[i];

		vertexData[i + 60] = f[i];
		vertexData[i + 63] = g[i];
		vertexData[i + 66] = h[i];
		vertexData[i + 69] = d[i];

	}

	changeVertexBuffer(72, vertexData);
	delete [] vertexData;

}

void CuboidObject::move(const glm::vec3 & mov) {

	setModelMatrix(glm::translate(getModelMatrix(), mov));

}