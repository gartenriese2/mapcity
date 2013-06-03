#include "Object.hpp"

Object::Object() {

	glGenVertexArrays(1, &m_vertexArray);

	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_indexBuffer);

	m_triangles = 0;
	m_modelMatrix = glm::mat4(1.f);

}

Object::~Object() {

	// glDeleteVertexArrays(1, &m_vertexArray);

	// glDeleteBuffers(1, &m_vertexBuffer);
	// glDeleteBuffers(1, &m_normalBuffer);
	// glDeleteBuffers(1, &m_colorBuffer);
	// glDeleteBuffers(1, &m_indexBuffer);

}

void Object::fillBuffers(int size, int indices, GLfloat * &vertexData, 
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

void Object::draw() {

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 3 * m_triangles, GL_UNSIGNED_SHORT, (void*)0);

}