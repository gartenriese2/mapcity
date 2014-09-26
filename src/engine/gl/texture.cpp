#include "texture.hpp"

#include "../debug.hpp"

namespace gl {

Texture::Texture() noexcept
  : gl::Object{GL_TEXTURE},
  	m_width{0},
  	m_height{0},
  	m_format{GL_NONE},
  	m_target{GL_NONE}
{
}

Texture::Texture(unsigned int width, unsigned int height, GLenum format, GLenum target) noexcept
  : gl::Object{GL_TEXTURE},
  	m_width{width},
  	m_height{height},
  	m_format{format},
  	m_target{target}
{
	glCreateTextures(m_target, 1, &m_name);
	glTextureStorage2D(m_name, 1, m_format, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));
}

Texture::Texture(const Texture & other) noexcept
  : gl::Object(other),
  	m_width{other.m_width},
  	m_height{other.m_height},
  	m_format{other.m_format},
  	m_target{other.m_target}
{
	glCreateTextures(m_target, 1, &m_name);
	glTextureStorage2D(m_name, 1, m_format, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));
	glCopyImageSubData(other, m_target, 1, 0, 0, 0, m_name, m_target, 1, 0, 0, 0,
		static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height), 1);
}

Texture::Texture(Texture && other) noexcept
  : Texture{}
{
	swap(*this, other);
}

Texture & Texture::operator=(Texture other) noexcept {
	swap(*this, other);
	return *this; 
}

Texture::~Texture() {

	glDeleteTextures(1, &m_name);

}

bool Texture::isValid() const {
	return glIsTexture(m_name);
}

void Texture::resize(unsigned int width, unsigned int height) {

	m_width = width;
	m_height = height;

	glDeleteTextures(1, &m_name);
	glCreateTextures(m_target, 1, &m_name);
	glTextureStorage2D(m_name, 1, m_format, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));

}

} // namespace gl
