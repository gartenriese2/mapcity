#include "PolygonObject.hpp"

PolygonObject::PolygonObject(const vectorVec3 & border, const glm::vec3 & center, const glm::vec3 & color) {

	m_border = border;
	m_center = center;
	m_color = color;

	initObject();

}

PolygonObject::~PolygonObject() {

}

void PolygonObject::initObject() {

	assert(m_border.size() > 2);

	unsigned long numTriangles = m_border.size();
	unsigned long numVertices = m_border.size() + 1;

	GLfloat * vertexData = new GLfloat[numVertices * 3];
	GLfloat * normalData = new GLfloat[numVertices * 3];
	GLfloat * colorData = new GLfloat[numVertices * 3];

	glm::vec3 normal = -glm::normalize(glm::cross(m_border[0] - m_center, m_border[1] - m_center));
	if (normal.y < 0) {
		std::reverse(m_border.begin(),m_border.end());
		normal = -glm::normalize(glm::cross(m_border[0] - m_center, m_border[1] - m_center));
	}

	vertexData[0] = m_center[0];
	vertexData[1] = m_center[1];
	vertexData[2] = m_center[2];
	normalData[0] = normal.x;
	normalData[1] = normal.y;
	normalData[2] = normal.z;
	colorData[0] = m_color.x;
	colorData[1] = m_color.y;
	colorData[2] = m_color.z;

	for (unsigned long i = 3; i < numVertices * 3; i += 3) {

		vertexData[i] = m_border[(i / 3) - 1][0];
		vertexData[i + 1] = m_border[(i / 3) - 1][1];
		vertexData[i + 2] = m_border[(i / 3) - 1][2];
		normalData[i] = normal.x;
		normalData[i + 1] = normal.y;
		normalData[i + 2] = normal.z;
		colorData[i] = m_color.x;
		colorData[i + 1] = m_color.y;
		colorData[i + 2] = m_color.z;

	}

	GLushort * indexData = new GLushort[numTriangles * 3];
	unsigned short count = 0;
	for (unsigned long i = 0; i < numTriangles * 3; i += 3)	{
		indexData[i] = 0;
		if (count + 2 > numTriangles) {
			indexData[i + 1] = 1;
		} else {
			indexData[i + 1] = count + 2;
		}
		indexData[i + 2] = count + 1;
		count++;
	}

	fillBuffers(numVertices * 3, numTriangles * 3, vertexData, normalData, colorData, indexData);
	delete [] vertexData;
	delete [] normalData;
	delete [] colorData;
	delete [] indexData;

	setTriangles(static_cast<int>(numTriangles));

}