#ifndef SHADER_HPP
#define SHADER_HPP

#include "ogl.h"
#include "glm.h"

#include <iostream>
#include <fstream>
#include <vector>

class Shader {
public:
	
	Shader(const char *, const char *);

	inline GLuint GetShaderID() { return m_shaderID; }
    inline void Use() { glUseProgram(m_shaderID); }

	GLuint addUniform(const char *);
	void linkMatrix4f(GLuint, const glm::mat4);
	void link3f(GLuint, const float, const float, const float);

private:
	GLuint m_shaderID;

	GLuint loadShaders(const char *,const char *);
};

#endif
