#include "vao.hpp"

#include "vbo.hpp"
#include "ibo.hpp"
#include "../debug.hpp"

#include <utility>

namespace gl {

VAO::VAO() noexcept
  : gl::Object(GL_VERTEX_ARRAY)
{
	glCreateVertexArrays(1, &m_name);
}

VAO & VAO::operator=(VAO && other) noexcept {
	swap(*this, other);
	return *this;
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &m_name);
}

bool VAO::isValid() const {
	return glIsVertexArray(m_name);
}

void VAO::draw(GLsizei size, GLenum mode, GLenum type) const {

	glBindVertexArray(m_name);
	glDrawElements(mode, size, type, static_cast<void *>(0));
	glBindVertexArray(0);

}

void VAO::attachVBO(const gl::VBO & vbo, GLuint index, GLuint attribindex) {

	attachBuffer(index, static_cast<GLint>(vbo.getChannels()), vbo.getType(), vbo.normalized(),
		0, vbo, static_cast<GLsizei>(vbo.getChannels() * vbo.getTypeSize()), attribindex);

}

void VAO::attachIBO(const gl::IBO & ibo) {

	attachIndexBuffer(ibo);

}

void VAO::attachBuffer(GLuint index, GLint size, GLenum type, bool normalized,
	GLuint offset, GLuint buffer, GLsizei stride, GLuint attribindex) {

	if (isValid()) {

		glEnableVertexArrayAttrib(m_name, attribindex);
		glVertexArrayAttribFormat(m_name, index, size, type, normalized, offset);
		glVertexArrayVertexBuffer(m_name, index, buffer, offset, stride);
		glVertexArrayAttribBinding(m_name, attribindex, index);

	}

}

void VAO::attachIndexBuffer(GLuint buffer) {

	if (isValid()) {

		glVertexArrayElementBuffer(m_name, buffer);

	}

}

} // namespace gl
