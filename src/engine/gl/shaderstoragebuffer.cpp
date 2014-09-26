#include "shaderstoragebuffer.hpp"

ShaderStorageBuffer::ShaderStorageBuffer() {

	glCreateBuffers(1, &m_name);

}

ShaderStorageBuffer::~ShaderStorageBuffer() {

	glDeleteBuffers(1, &m_name);

}

void ShaderStorageBuffer::bindTo(unsigned int to) {

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, to, m_name);

}
