#ifndef _VBO_
#define _VBO_

#include "glincludes.hpp"
#include "buffer.hpp"

#include <vector>

namespace gl {

class VBO : public gl::Buffer {

		static constexpr GLuint k_defaultChannelSize {4};

	public:

		VBO(GLuint = k_defaultChannelSize) noexcept;
		VBO(const VBO &) = default;
		VBO(VBO &&) noexcept;
		VBO & operator=(VBO) noexcept;
		virtual ~VBO() {}

		GLuint getChannels() const { return m_channels; }
		GLenum getType() const { return GL_FLOAT; }
		GLuint getTypeSize() const { return sizeof(GLfloat); }
		GLuint getSize() const { return getByteSize() / getTypeSize(); }
		bool normalized() const { return false; }

		void insertData(const std::vector<GLfloat> &, GLenum = GL_STATIC_DRAW);

	protected:

		friend void swap(VBO & a, VBO & b) noexcept {
			using std::swap;
			swap(static_cast<gl::Buffer &>(a), static_cast<gl::Buffer &>(b));
			swap(a.m_channels, b.m_channels);
		}

		GLuint m_channels;

};

} // namespace gl

#endif // _VBO_
