#ifndef SHADER_HPP
#define SHADER_HPP

#include "ogl.h"
#include "glm.h"

#include <iostream>
#include <fstream>
#include <vector>

struct TextureUniform {
    
    GLenum target;
    GLuint texture;
    GLint ID;

};

class Shader {
	
	public:
		
		Shader(const char *, const char *);

		GLuint GetShaderID() const { return m_shaderID; }
	    void Use() const { glUseProgram(m_shaderID); }

		void addUniformTexture(const GLenum, const GLuint, const char *);
		GLint addUniform(const char *) const;
		void linkTextures() const;
		void link(const GLint, const glm::mat4 &) const;
		void link(const GLint, const float, const float, const float) const;

	private:
		
		GLuint m_shaderID;

		std::vector<TextureUniform> m_textureUniforms;

		GLuint loadShaders(const char *,const char *);
};

#endif
