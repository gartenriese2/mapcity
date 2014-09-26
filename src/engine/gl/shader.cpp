#include "shader.hpp"

#include "../debug.hpp"

#include <fstream>
#include <vector>

Shader::Shader(const std::string & file) {

	if (file.size() < 6 && file[file.size() - 5] != '.') {
		Debug::log("Not a valid shader file!");
		exit(0);
	}

	std::string type = file.substr(file.size() - 4);
	if (type == "vert") {
		m_shader = glCreateShader(GL_VERTEX_SHADER);
	} else if (type == "frag") {
		m_shader = glCreateShader(GL_FRAGMENT_SHADER);
	} else if (type == "geom") {
		m_shader = glCreateShader(GL_GEOMETRY_SHADER);
	} else if (type == "cont") {
		m_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	} else if (type == "eval") {
		m_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	} else if (type == "comp") {
		m_shader = glCreateShader(GL_COMPUTE_SHADER);
	} else {
		Debug::log("Not a valid shader file ending: " + type);
		exit(0);
	}

	if (m_shader == 0) {
		Debug::log("Error allocating shader object!");
	}

	const std::string code = getShaderCode(file);
	const char * charcode = code.c_str();
	const GLint len = static_cast<GLint>(code.size());
	glShaderSource(m_shader, 1, &charcode, &len);

	glCompileShader(m_shader);

	GLint success = GL_FALSE;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

	if (!success) {

		GLint logSize = 0;
		glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logSize);

		std::vector<char> tmp;
		tmp.reserve(static_cast<size_t>(logSize));
		glGetShaderInfoLog(m_shader, logSize, NULL, &tmp[0]);

		Debug::log(file + ": Shader compiling failed with the following error:\n");
		Debug::log(&tmp[0]);
		exit(0);

	}

}

Shader::~Shader() {

	glDeleteShader(m_shader);

}

const std::string Shader::getShaderCode(const std::string & file) const {

	std::string code;
	std::ifstream stream(file, std::ifstream::in);
	while (stream.good()) {
		std::string tmp;
		std::getline(stream, tmp);
		code += tmp + "\n";
	}
	stream.close();
	return code;

}
