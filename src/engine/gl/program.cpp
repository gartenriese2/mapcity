#include "program.hpp"

#include "../debug.hpp"

#include <vector>

Program::Program()
  : m_linked(false)
{

	m_program = glCreateProgram();

	if (m_program == 0) {
		Debug::log("Error creating Program!");
	}

}

Program::~Program() {

	glDeleteProgram(m_program);

}

Uniform Program::operator[](const std::string & name) const {
	
	auto it = m_uniforms.find(name);
	if (it != m_uniforms.end()) {
		return Uniform(it->second);
	}
	return Uniform(-1);
		
}


void Program::attachShader(const Shader & shader) const {
	
	glAttachShader(m_program, shader());

}

void Program::link() {

	glLinkProgram(m_program);

	GLint success = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	
	if (!success) {

		GLint logSize = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);

		std::vector<char> tmp;
		tmp.reserve(static_cast<size_t>(logSize));
		glGetProgramInfoLog(m_program, logSize, NULL, &tmp[0]);

		Debug::log("Program linking failed with the following error:\n");
		if (tmp.size() != 0) Debug::log(tmp[0]);
		exit(0);

	}

	m_linked = true;

	m_uniforms.clear();

	GLint numUniforms;
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, & numUniforms);
	GLint maxLength;
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, & maxLength);
	std::unique_ptr<char[]> buffer{new char[static_cast<unsigned long>(maxLength)]};
	GLint size = 1;
	GLsizei length = 1;
	GLenum type = 0;
	for (GLuint i = 0; i < static_cast<GLuint>(numUniforms); ++i) {
		
		glGetActiveUniform(m_program, i, maxLength, &length, &size, &type, buffer.get());
		m_uniforms.emplace(std::string(buffer.get()), i);

	}

}

void Program::use() {

	if (!m_linked) {
		link();
	}

	glUseProgram(m_program);

}
