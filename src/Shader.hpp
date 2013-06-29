#ifndef SHADER_HPP
#define SHADER_HPP

#include "ogl.h"
#include "glm.h"

#include <iostream>
#include <fstream>
#include <vector>

struct TextureUniform
{
    GLenum target;
    GLuint texture;
    GLuint ID;
};

class Shader {
public:
	
	Shader(const char *, const char *);

	inline GLuint GetShaderID() { return m_shaderID; }
    inline void Use() { glUseProgram(m_shaderID); }

	void addUniformTexture(const GLenum, const GLuint, const char *);
	GLuint addUniform(const char *);
	void linkTextures();
	void link(GLuint, const glm::mat4);
	void link(GLuint, const float, const float, const float);

private:
	GLuint m_shaderID;

	std::vector<TextureUniform> m_textureUniforms;

	GLuint loadShaders(const char *,const char *);
};

#endif
