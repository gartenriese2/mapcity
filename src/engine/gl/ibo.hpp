#ifndef _IBO_
#define _IBO_

#include "glincludes.hpp"
#include "buffer.hpp"

#include <vector>

namespace gl {

class IBO : public gl::Buffer {

	public:

		IBO() noexcept;
		IBO(const IBO &) = default;
		IBO(IBO &&) noexcept;
		IBO & operator=(IBO) noexcept;
		virtual ~IBO() {}

		GLuint getTypeSize() const { return sizeof(GLushort); }
		GLuint getSize() const { return getByteSize() / getTypeSize(); }

		void insertData(const std::vector<GLushort> &);

	protected:

		friend void swap(IBO & a, IBO & b) noexcept {
			using std::swap;
			swap(static_cast<gl::Buffer &>(a), static_cast<gl::Buffer &>(b));
		}

};

} // namespace gl

#endif // _IBO_
