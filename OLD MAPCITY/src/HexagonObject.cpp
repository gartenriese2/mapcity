#include "HexagonObject.hpp"

HexagonObject::HexagonObject(const glm::vec3 & center, const glm::vec3 & side, const glm::vec3 & color) {

	m_center = center;
	m_side = side;
	m_color = color;

	initObject();

}

HexagonObject::~HexagonObject() {

}

void HexagonObject::initObject() {

	GLfloat * vertexData = new GLfloat[21];
	GLfloat * normalData = new GLfloat[21];
	GLfloat * colorData = new GLfloat[21];

	glm::vec3 centerToSide = m_side - m_center;
	float factor = glm::sqrt((glm::pow(centerToSide.x, 2.f) + glm::pow(centerToSide.y, 2.f) + glm::pow(centerToSide.z, 2.f)) * 3.f) / 2.f;
	glm::vec3 up = glm::normalize(glm::vec3(centerToSide.z, 0, centerToSide.x));
	up *= factor;
	
	glm::vec3 upperleft = m_center + centerToSide / 2.f + up;
	glm::vec3 upperright = m_center - centerToSide / 2.f + up;
	glm::vec3 right = m_center - centerToSide;
	glm::vec3 lowerright = m_center - centerToSide / 2.f - up;
	glm::vec3 lowerleft = m_center + centerToSide / 2.f - up;

	glm::vec3 normal = glm::normalize(glm::cross(up, centerToSide));

	for (unsigned long i = 0; i < 3; i++) {

		vertexData[i] = m_center[i];
		vertexData[i + 3] = m_side[i];
		vertexData[i + 6] = lowerleft[i];
		vertexData[i + 9] = lowerright[i];
		vertexData[i + 12] = right[i];
		vertexData[i + 15] = upperright[i];
		vertexData[i + 18] = upperleft[i];

	}

	for (unsigned long i = 0; i < 21; i += 3) {
		normalData[i] = normal.x;
		normalData[i + 1] = normal.y;
		normalData[i + 2] = normal.z;
		colorData[i] = m_color.x;
		colorData[i + 1] = m_color.y;
		colorData[i + 2] = m_color.z;
	}

	GLushort * indexData = new GLushort[18];
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;

	indexData[3] = 0;
	indexData[4] = 2;
	indexData[5] = 3;

	indexData[6] = 0;
	indexData[7] = 3;
	indexData[8] = 4;

	indexData[9] = 0;
	indexData[10] = 4;
	indexData[11] = 5;

	indexData[12] = 0;
	indexData[13] = 5;
	indexData[14] = 6;

	indexData[15] = 0;
	indexData[16] = 6;
	indexData[17] = 1;

	fillBuffers(21, 18, vertexData, normalData, colorData, indexData);
	delete [] vertexData;
	delete [] normalData;
	delete [] colorData;
	delete [] indexData;

	setTriangles(6);

}

void HexagonObject::changeColor(const glm::vec3 & color) {

	m_color = color;

	GLfloat * colorData = new GLfloat[21];
	for (unsigned long i = 0; i < 21; i += 3) {
		colorData[i] = m_color.x;
		colorData[i + 1] = m_color.y;
		colorData[i + 2] = m_color.z;
	}

	changeColorBuffer(21, colorData);
	delete [] colorData;

}