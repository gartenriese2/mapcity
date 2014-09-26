#ifndef _GL_OBJECT_
#define _GL_OBJECT_

#include "glincludes.hpp"
#include "../debug.hpp"

#include <string>

namespace gl {

class Object {

	public:

		virtual operator GLuint() const final { return m_name; }

		const std::string getLabel();
		void setLabel(const std::string &);

	protected:

		Object(GLenum) noexcept;
		Object(const Object &) noexcept;
		Object(Object &&) noexcept;
		Object & operator=(Object) noexcept;
		virtual ~Object();

		virtual bool isValid() const { return false; }

		friend void swap(Object & a, Object & b) noexcept {
			using std::swap;
			swap(a.m_name, b.m_name);
			swap(a.m_identifier, b.m_identifier);
		}

		GLuint m_name;
		GLenum m_identifier;

};

} // namespace gl

#endif // _GL_OBJECT_
