#ifndef _VAO_
#define _VAO_

#include "glincludes.hpp"
#include "globject.hpp"

#include <string>

namespace gl {

class VBO;
class IBO;

class VAO : public gl::Object {

	public:

		VAO() noexcept;
		VAO(VAO && v) noexcept;
		VAO & operator=(VAO &&) noexcept;
		virtual ~VAO();

		virtual bool isValid() const;

		void attachVBO(const gl::VBO &, GLuint, GLuint);
		void attachIBO(const gl::IBO &);

		void draw(GLsizei, GLenum = GL_TRIANGLES, GLenum = GL_UNSIGNED_SHORT) const;

	protected:

		void attachBuffer(GLuint, GLint, GLenum, bool, GLuint, GLuint, GLsizei, GLuint);
		void attachIndexBuffer(GLuint);

		friend void swap(VAO & a, VAO & b) noexcept {
			using std::swap;
			swap(static_cast<gl::Object &>(a), static_cast<gl::Object &>(b));
		}

	private:

		VAO(const VAO &) = delete;
		VAO & operator=(VAO) = delete;
		VAO & operator=(const VAO &) = delete;

};

} // namespace gl

#endif // _VAO_
