#include "buffer.hpp"

#include "../debug.hpp"

namespace gl {

Buffer::Buffer() noexcept
  : gl::Object{GL_BUFFER}
{
	glCreateBuffers(1, &m_name);
}

Buffer::Buffer(const Buffer & other) noexcept
  : gl::Object{other}
{

	glCreateBuffers(1, &m_name);

	if (other.isValid()) {

		GLuint otherSize {other.getByteSize()};

		glNamedBufferData(m_name, otherSize, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, otherSize);

	}

}

Buffer::Buffer(Buffer && other) noexcept
  : Buffer{}
{
	swap(*this, other);
}

Buffer & Buffer::operator=(Buffer other) noexcept {
	swap(*this, other);
	return *this;
};

Buffer::~Buffer() {

	if (isValid()) {
		
		glNamedBufferData(m_name, 0, nullptr, GL_STREAM_DRAW);
		glDeleteBuffers(1, &m_name);

	}

}

bool Buffer::isValid() const {

	return glIsBuffer(m_name);

}

GLuint Buffer::getByteSize() const {

	GLint size {0};

	if (isValid()){
		glGetNamedBufferParameteriv(m_name, GL_BUFFER_SIZE, &size);
	}

	return static_cast<GLuint>(size);

}

}
