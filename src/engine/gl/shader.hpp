#ifndef _SHADER_
#define _SHADER_

#include "glincludes.hpp"

#include <string>

class Shader {

	public:

		Shader(const std::string &);
		Shader(const Shader &) = delete;
		Shader(Shader &&) = delete;
		Shader & operator=(const Shader &) = delete;
		Shader & operator=(Shader &&) = delete;
		~Shader();

		GLuint operator()() const { return m_shader; }

	private:

		GLuint m_shader;

		const std::string getShaderCode(const std::string &) const;

};

#endif // _SHADER_