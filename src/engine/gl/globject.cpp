#include "globject.hpp"

namespace gl {

Object::Object(GLenum identifier) noexcept
  : m_name{0},
  	m_identifier{identifier}
{
}

Object::Object(const Object & other) noexcept
  : m_name{other.m_name},
    m_identifier{other.m_identifier}
{
}

Object::Object(Object && other) noexcept
  : Object(GL_NONE)
{
	swap(*this, other);
}

Object & Object::operator=(Object other) noexcept {
    swap(*this, other);
    return *this;
}

Object::~Object() {
	m_name = 0;
	m_identifier = GL_NONE;
}

void Object::setLabel(const std::string & name) {
	
	const std::string str = name.substr(0, GL_MAX_LABEL_LENGTH);
	
	glObjectLabel(m_identifier, m_name, static_cast<GLsizei>(str.size()), str.c_str());DEB

}

const std::string Object::getLabel() {

	GLint size {0};
	glGetIntegerv(GL_MAX_LABEL_LENGTH, &size);
	/*GLchar label[size];*/ // NO VLA
	GLchar label[1024];
	GLsizei len {0};

	glGetObjectLabel(m_identifier, m_name, size, &len, label);
	
	return label;

}

} // namespace gl
