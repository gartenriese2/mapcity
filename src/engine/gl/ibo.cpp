#include "ibo.hpp"

#include <utility>

namespace gl {

IBO::IBO() noexcept
  : gl::Buffer{}
{
}

IBO::IBO(IBO && other) noexcept
  : IBO{}
{
	swap(*this, other);
}

IBO & IBO::operator=(IBO other) noexcept {
	swap(*this, other);
	return *this;
}

void IBO::insertData(const std::vector<GLushort> & data) {

	if (isValid()) {
		glNamedBufferData(m_name, static_cast<GLsizeiptr>(data.size() * sizeof(GLushort)), &data[0], GL_STATIC_DRAW);
	}

}

} // namespace gl
