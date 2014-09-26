#include "vbo.hpp"

namespace gl {

VBO::VBO(GLuint size) noexcept
  : gl::Buffer{},
  	m_channels{size}
{
}

VBO::VBO(VBO && other) noexcept
  : VBO{k_defaultChannelSize}
{
	swap(*this, other);
}

VBO & VBO::operator=(VBO other) noexcept {
	swap(*this, other);
	return *this;
}

void VBO::insertData(const std::vector<GLfloat> & data, GLenum usage) {
	
	if (isValid()) {
		glNamedBufferData(m_name, static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat)), &data[0], usage);
	}

}

} // namespace gl
