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

	// taken from http://www.lighthouse3d.com/opengl/glsl/index.php?oglinfo
	void printShaderInfoLog( GLuint );
	void printProgramInfoLog( GLuint );

public:
	inline GLuint getId() { return program; };
	bool load( std::string );
	bool compile();
	Shader();
	~Shader();
	void bind();
	void unbind();
};

}

#endif