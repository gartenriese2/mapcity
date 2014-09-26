#ifndef _TEXTURE_
#define _TEXTURE_

#include "glincludes.hpp"
#include "globject.hpp"

namespace gl {

class Texture : public gl::Object {

	public:

		Texture() noexcept;
		Texture(unsigned int, unsigned int, GLenum = GL_RGBA32F, GLenum = GL_TEXTURE_2D) noexcept;
		Texture(const Texture &) noexcept;
		Texture(Texture &&) noexcept;
		Texture & operator=(Texture) noexcept;
		virtual ~Texture();

		virtual bool isValid() const override;
		
		void resize(unsigned int, unsigned int);

	private:

		friend void swap(Texture & a, Texture & b) noexcept {
			using std::swap;
			swap(static_cast<gl::Object &>(a), static_cast<gl::Object &>(b));
			swap(a.m_width, b.m_width);
			swap(a.m_height, b.m_height);
			swap(a.m_format, b.m_format);
			swap(a.m_target, b.m_target);
		}

		unsigned int m_width;
		unsigned int m_height;
		GLenum m_format;
		GLenum m_target;

};

} // namespace gl

#endif // _TEXTURE_
