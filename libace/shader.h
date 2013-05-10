/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef SHADER_H
#define SHADER_H

#include "ogl.h"
#include "stl.h"

// Libace
#include "error.h"
#include "mesh.h"

namespace ace {

class Shader {
private:
	GLuint program;
	enum {
		FRAGMENT_MODE,
		VERTEX_MODE,
		UNDEF_MODE
	};
	std::string m_vertex;
	std::string m_fragment;

	std::map<std::string, unsigned int> m_attributeList;
	std::map<std::string, unsigned int> m_uniformList;

	// taken from http://www.lighthouse3d.com/opengl/glsl/index.php?oglinfo
	void printShaderInfoLog( GLuint );
	void printProgramInfoLog( GLuint );

public:
	inline GLuint getId() { return program; };
	bool load( const std::string );
	bool compile();
	Shader();
	Shader( const std::string );
	~Shader();
	void bind();
	void unbind();
	void addAttribute( const std::string attr, unsigned int v );
	void addUniform( const std::string uniform, float v );
	void addUniform( const std::string uniform, unsigned int v );
	void addUniform( const std::string uniform, float *v );
};

}

#endif