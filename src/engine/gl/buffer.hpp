#ifndef _BUFFER_
#define _BUFFER_

#include "glincludes.hpp"
#include "globject.hpp"

#include <vector>

namespace gl {

class Buffer : public gl::Object {

	public:

		Buffer() noexcept;
		Buffer(const Buffer &) noexcept;
		Buffer(Buffer &&) noexcept;
		Buffer & operator=(Buffer) noexcept;
		virtual ~Buffer();

		virtual bool isValid() const override;

		GLuint getByteSize() const;

	protected:

		friend void swap(Buffer & a, Buffer & b) noexcept {
			using std::swap;
			swap(static_cast<gl::Object &>(a), static_cast<gl::Object &>(b));
		}

};

}

#endif // _BUFFER_