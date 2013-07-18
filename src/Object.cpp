#include "Object.hpp"

Object::Object() {

	init();

}

Object::~Object() {

	// glDeleteVertexArrays(1, &m_vertexArray);

	// glDeleteBuffers(1, &m_vertexBuffer);
	// glDeleteBuffers(1, &m_normalBuffer);
	// glDeleteBuffers(1, &m_colorBuffer);
	// glDeleteBuffers(1, &m_indexBuffer);

}

void Object::init() {

	glGenVertexArrays(1, &m_vertexArray);

	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_indexBuffer);

	m_triangles = 0;
	m_modelMatrix = glm::mat4(1.f);

}

void Object::fillBuffers(const unsigned long size, const unsigned long indices, GLfloat * &vertexData, 
					GLfloat * &normalData, GLfloat * &colorData, GLushort * &indexData) {

	glBindVertexArray(m_vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, normalData, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, colorData, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices, indexData, GL_STATIC_DRAW);

}

void Object::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 3 * m_triangles, GL_UNSIGNED_SHORT, (void*)0);

}

void Object::createCuboidData(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, 
						const glm::vec3 & d, GLfloat * & vertexData, GLfloat * & normalData, GLushort * & indexData) {
	
	vertexData = new GLfloat[72];
	normalData = new GLfloat[72];
	indexData = new GLushort[36];

	glm::vec3 e = c + (b - a);
	glm::vec3 f = d + (c - a);
	glm::vec3 g = e + (d - a);
	glm::vec3 h = g + (a - c);
	glm::vec3 n1 = glm::normalize(glm::cross(a - b, c - b));
	glm::vec3 n2 = glm::normalize(glm::cross(d - a, f - a));
	glm::vec3 n3 = glm::normalize(glm::cross(c - e, f - e));

	for (unsigned long i = 0; i < 3; i++) {
		
		vertexData[i + 0] = a[i];
		vertexData[i + 3] = b[i];
		vertexData[i + 6] = e[i];
		vertexData[i + 9] = c[i];
		normalData[i + 0] = n1[i];
		normalData[i + 3] = n1[i];
		normalData[i + 6] = n1[i];
		normalData[i + 9] = n1[i];

		vertexData[i + 12] = a[i];
		vertexData[i + 15] = c[i];
		vertexData[i + 18] = f[i];
		vertexData[i + 21] = d[i];
		normalData[i + 12] = n2[i];
		normalData[i + 15] = n2[i];
		normalData[i + 18] = n2[i];
		normalData[i + 21] = n2[i];

		vertexData[i + 24] = c[i];
		vertexData[i + 27] = e[i];
		vertexData[i + 30] = g[i];
		vertexData[i + 33] = f[i];
		normalData[i + 24] = n3[i];
		normalData[i + 27] = n3[i];
		normalData[i + 30] = n3[i];
		normalData[i + 33] = n3[i];

		vertexData[i + 36] = a[i];
		vertexData[i + 39] = d[i];
		vertexData[i + 42] = h[i];
		vertexData[i + 45] = b[i];
		normalData[i + 36] = -n3[i];
		normalData[i + 39] = -n3[i];
		normalData[i + 42] = -n3[i];
		normalData[i + 45] = -n3[i];
		
		vertexData[i + 48] = e[i];
		vertexData[i + 51] = b[i];
		vertexData[i + 54] = h[i];
		vertexData[i + 57] = g[i];
		normalData[i + 48] = -n2[i];
		normalData[i + 51] = -n2[i];
		normalData[i + 54] = -n2[i];
		normalData[i + 57] = -n2[i];

		vertexData[i + 60] = f[i];
		vertexData[i + 63] = g[i];
		vertexData[i + 66] = h[i];
		vertexData[i + 69] = d[i];
		normalData[i + 60] = -n1[i];
		normalData[i + 63] = -n1[i];
		normalData[i + 66] = -n1[i];
		normalData[i + 69] = -n1[i];

	}

	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	indexData[3] = 2;
	indexData[4] = 3;
	indexData[5] = 0;

	indexData[6] = 4;
	indexData[7] = 5;
	indexData[8] = 6;
	indexData[9] = 6;
	indexData[10] = 7;
	indexData[11] = 4;

	indexData[12] = 8;
	indexData[13] = 9;
	indexData[14] = 10;
	indexData[15] = 10;
	indexData[16] = 11;
	indexData[17] = 8;

	indexData[18] = 12;
	indexData[19] = 13;
	indexData[20] = 14;
	indexData[21] = 14;
	indexData[22] = 15;
	indexData[23] = 12;

	indexData[24] = 16;
	indexData[25] = 17;
	indexData[26] = 18;
	indexData[27] = 18;
	indexData[28] = 19;
	indexData[29] = 16;

	indexData[30] = 20;
	indexData[31] = 21;
	indexData[32] = 22;
	indexData[33] = 22;
	indexData[34] = 23;
	indexData[35] = 20;

}

glm::vec3 Object::drawHermite(const glm::vec3 & A, const glm::vec3 & B, const glm::vec3 & mA, const glm::vec3 & mB, const float t) {

	float t3 = glm::pow(t, 3.f);
	float t2 = glm::pow(t, 2.f);

	return (2*t3 - 3*t2 + 1) * A + (t3 - 2*t2 + t) * mA + (3*t2 - 2*t3) * B + (t3 - t2) * mB;

}

void Object::addQuadToData(	std::vector<GLfloat> & vertexData,
							std::vector<GLfloat> & normalData,
							std::vector<GLushort> & indexData,
							std::vector<GLfloat> & colorData,
							const glm::vec3 & start,
							const glm::vec3 & end,
							const float width,
							const glm::vec3 & color) {

	glm::vec3 l = end - start;
	glm::vec3 a = start + glm::normalize(glm::vec3(l.z, 0, -l.x)) * width / 2.f;
	glm::vec3 b = start + glm::normalize(glm::vec3(-l.z, 0, l.x)) * width / 2.f;
	glm::vec3 c = end + glm::normalize(glm::vec3(-l.z, 0, l.x)) * width / 2.f;
	glm::vec3 d = end + glm::normalize(glm::vec3(l.z, 0, -l.x)) * width / 2.f;

	unsigned short len = static_cast<unsigned short>(vertexData.size()) / 3;

	vertexData.push_back(a[0]);
	vertexData.push_back(a[1]);
	vertexData.push_back(a[2]);

	vertexData.push_back(b[0]);
	vertexData.push_back(b[1]);
	vertexData.push_back(b[2]);

	vertexData.push_back(c[0]);
	vertexData.push_back(c[1]);
	vertexData.push_back(c[2]);

	vertexData.push_back(d[0]);
	vertexData.push_back(d[1]);
	vertexData.push_back(d[2]);

	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));
	for (int i = 0; i < 4; i++) {
		normalData.push_back(n[0]);
		normalData.push_back(n[1]);
		normalData.push_back(n[2]);
	}

	for (int i = 0; i < 4; i++) {
		colorData.push_back(color[0]);
		colorData.push_back(color[1]);
		colorData.push_back(color[2]);
	}

	indexData.push_back(len);
	indexData.push_back(len + 1);
	indexData.push_back(len + 2);
	indexData.push_back(len + 2);
	indexData.push_back(len + 3);
	indexData.push_back(len);

}

void Object::addQuadToData(	std::vector<GLfloat> & vertexData,
							std::vector<GLfloat> & normalData,
							std::vector<GLushort> & indexData,
							std::vector<GLfloat> & colorData,
							const vectorVec3 & pts,
							const glm::vec3 & color) {

	assert(pts.size() == 4);

	glm::vec3 a = pts[0];
	glm::vec3 b = pts[3];
	glm::vec3 c = pts[2];
	glm::vec3 d = pts[1];

	unsigned short len = static_cast<unsigned short>(vertexData.size()) / 3;

	vertexData.push_back(a[0]);
	vertexData.push_back(a[1]);
	vertexData.push_back(a[2]);

	vertexData.push_back(b[0]);
	vertexData.push_back(b[1]);
	vertexData.push_back(b[2]);

	vertexData.push_back(c[0]);
	vertexData.push_back(c[1]);
	vertexData.push_back(c[2]);

	vertexData.push_back(d[0]);
	vertexData.push_back(d[1]);
	vertexData.push_back(d[2]);

	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));
	for (int i = 0; i < 4; i++) {
		normalData.push_back(n[0]);
		normalData.push_back(n[1]);
		normalData.push_back(n[2]);
	}

	for (int i = 0; i < 4; i++) {
		colorData.push_back(color[0]);
		colorData.push_back(color[1]);
		colorData.push_back(color[2]);
	}

	indexData.push_back(len);
	indexData.push_back(len + 1);
	indexData.push_back(len + 2);
	indexData.push_back(len + 2);
	indexData.push_back(len + 3);
	indexData.push_back(len);

}