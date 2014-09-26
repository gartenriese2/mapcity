#include "object.hpp"

#include "../debug.hpp"
#include "../handler.hpp"

static const glm::vec3 k_defaultColor {1.f, 0.f, 0.f};

Object::Object(const Object & other)
  : m_vaoPtr(new gl::VAO()),
  	m_vertexBufferPtr(new gl::VBO(*other.m_vertexBufferPtr)),
  	m_colorBufferPtr(new gl::VBO(*other.m_colorBufferPtr)),
  	m_normalBufferPtr(new gl::VBO(*other.m_normalBufferPtr)),
  	m_indexBufferPtr(new gl::IBO(*other.m_indexBufferPtr)),
  	m_modelMatrix(other.m_modelMatrix),
  	m_scaleMatrix(other.m_scaleMatrix),
  	m_rotationMatrix(other.m_rotationMatrix),
  	m_translationMatrix(other.m_translationMatrix),
  	m_center(other.m_center),
  	m_actualPosition(other.m_actualPosition),
  	m_actualScale(other.m_actualScale)
{
	attachBuffers();
}

void Object::init() {

	m_vaoPtr = std::make_shared<gl::VAO>();
	m_vertexBufferPtr = std::make_shared<gl::VBO>(3);
  	m_colorBufferPtr = std::make_shared<gl::VBO>(3);
  	m_normalBufferPtr = std::make_shared<gl::VBO>(3);
  	m_indexBufferPtr = std::make_shared<gl::IBO>();
  	m_modelMatrix = glm::mat4(1.f);
  	m_scaleMatrix = glm::mat4(1.f);
  	m_rotationMatrix = glm::mat4(1.f);
  	m_translationMatrix = glm::mat4(1.f);
  	m_actualScale = {1.f, 1.f, 1.f};

  	attachBuffers();

}

void Object::attachBuffers() {

	m_vaoPtr->attachIBO(*m_indexBufferPtr);
	m_vaoPtr->attachVBO(*m_vertexBufferPtr, 0, 0);
	m_vaoPtr->attachVBO(*m_colorBufferPtr, 1, 1);
	m_vaoPtr->attachVBO(*m_normalBufferPtr, 2, 2);

}

void Object::makeInstance(const Object & other) {

	m_vaoPtr = std::make_shared<gl::VAO>();
	m_vertexBufferPtr = other.m_vertexBufferPtr;
	m_colorBufferPtr = std::make_shared<gl::VBO>(*other.m_colorBufferPtr);
	m_normalBufferPtr = other.m_normalBufferPtr;
	m_indexBufferPtr = other.m_indexBufferPtr;
	m_modelMatrix = other.m_modelMatrix;
	m_scaleMatrix = other.m_scaleMatrix;
	m_rotationMatrix = other.m_rotationMatrix;
	m_translationMatrix = other.m_translationMatrix;
	m_center = other.m_center;
	m_actualPosition = other.m_actualPosition;
	m_actualScale = other.m_actualScale;

	attachBuffers();

}

void Object::rotate(float radians, const glm::vec3 & axis) {

	if (glm::length(axis) != 0.f) {

		m_rotationMatrix = glm::translate(m_rotationMatrix, m_center);
		m_rotationMatrix = glm::rotate(m_rotationMatrix, radians, axis);
		m_rotationMatrix = glm::translate(m_rotationMatrix, -m_center);
		m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;

	}

}

void Object::rotateAround(float radians, const glm::vec3 & axis, const glm::vec3 & point) {

	if (glm::length(axis) != 0.f) {
		
		rotate(radians, axis);

		// http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html -> Section 6.2
		float x = m_actualPosition.x;
		float y = m_actualPosition.y;
		float z = m_actualPosition.z;
		float a = point.x;
		float b = point.y;
		float c = point.z;
		glm::vec3 nAxis = glm::normalize(axis);
		float u = nAxis.x;
		float v = nAxis.y;
		float w = nAxis.z;

		float retX = (a * (v*v + w*w) - u * (b*v + c*w - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ x * glm::cos(radians) + (-c*v + b*w - w*y + v*z) * glm::sin(radians);
		float retY = (b * (u*u + w*w) - v * (a*u + c*w - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ y * glm::cos(radians) + (c*u - a*w + w*x - u*z) * glm::sin(radians);
		float retZ = (c * (u*u + v*v) - w * (a*u + b*v - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ z * glm::cos(radians) + (-b*u + a*v - v*x + u*y) * glm::sin(radians);

		moveTo({retX, retY, retZ});

	}

}

void Object::move(float val, const glm::vec3 & dir) {

	if (glm::length(dir) != 0.f) {

		m_translationMatrix = glm::translate(m_translationMatrix, val * dir);
		m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
		m_actualPosition += (val * dir);

	}

}

void Object::moveTo(const glm::vec3 & to) {

	m_translationMatrix = glm::translate(m_translationMatrix, to - m_actualPosition);
	m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
	m_actualPosition = to;

}

void Object::scale(const glm::vec3 & val) {

	if (glm::length(val) != 0.f) {

		m_scaleMatrix = glm::translate(m_scaleMatrix, m_center);
		m_scaleMatrix = glm::scale(m_scaleMatrix, val);
		m_scaleMatrix = glm::translate(m_scaleMatrix, -m_center);
		m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;

	}

}

void Object::scaleColor(float scale) {

	GLuint size = m_colorBufferPtr->getSize();

	GLfloat * data = (GLfloat *) glMapNamedBuffer(*m_colorBufferPtr, GL_READ_WRITE);

	if (data != (GLfloat *) nullptr) {
		for(GLuint i = 0; i < size; ++i) {
        	data[i] *= scale;
        }
		glUnmapNamedBuffer(*m_colorBufferPtr);
	} else {
		Debug::log("glMapBuffer failed!");
	}

}

void Object::setColor(const std::initializer_list<glm::vec3> & colors) {

	m_colorBufferPtr->insertData(getColorVector(colors, static_cast<unsigned int>(m_colorBufferPtr->getByteSize())));

}

void Object::setColor(const glm::vec3 & color) {

	m_colorBufferPtr->insertData(getColorVector(color, static_cast<unsigned int>(m_colorBufferPtr->getByteSize())));

}

void Object::setCenter(const glm::vec3 & center) {

	m_center = center;
	m_actualPosition = center;

}

const std::vector<GLfloat> Object::getColorVector(const std::initializer_list<glm::vec3> & colors, unsigned int maxSize) const {

	std::vector<GLfloat> v;

	for (const auto & color : colors) {
		
		if (&color - colors.begin() >= maxSize) return v;

		v.emplace_back(color.x);
		v.emplace_back(color.y);
		v.emplace_back(color.z);

	}

	for (unsigned int i = static_cast<unsigned int>(v.size()) / 3; i < maxSize; ++i) {
		
		v.emplace_back(k_defaultColor[0]);
		v.emplace_back(k_defaultColor[1]);
		v.emplace_back(k_defaultColor[2]);

	}

	return v;

}

const std::vector<GLfloat> Object::getColorVector(const glm::vec3 & color, unsigned int maxSize) const {

	std::vector<GLfloat> v;

	for (unsigned int i = 0; i < maxSize; ++i) {
		
		v.emplace_back(color.x);
		v.emplace_back(color.y);
		v.emplace_back(color.z);

	}

	return v;

}

void Object::fillTriangles(const std::vector<GLushort> & indices, const std::vector<GLfloat> & vertices) {

	for (unsigned int i = 0; i < indices.size(); i += 3) {

		glm::vec4 a = glm::vec4(vertices[3 * indices[i]],
			vertices[3 * indices[i] + 1], vertices[3 * indices[i] + 2], 1.f);
		glm::vec4 b = glm::vec4(vertices[3 * indices[i + 1]],
			vertices[3 * indices[i + 1] + 1], vertices[3 * indices[i + 1] + 2], 1.f);
		glm::vec4 c = glm::vec4(vertices[3 * indices[i + 2]],
			vertices[3 * indices[i + 2] + 1], vertices[3 * indices[i + 2] + 2], 1.f);

		m_triangles.emplace_back(a, b, c);

	}
	
}
