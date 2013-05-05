/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// OpenGL 
#include "ogl.h"

// libace
#include "texture.h"
#include "error.h"

namespace ace {

static GLenum colorattachment[] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4,
		GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6,
		GL_COLOR_ATTACHMENT7,
		GL_COLOR_ATTACHMENT8,
		GL_COLOR_ATTACHMENT9,
		GL_COLOR_ATTACHMENT10,
		GL_COLOR_ATTACHMENT11,
		GL_COLOR_ATTACHMENT12,
		GL_COLOR_ATTACHMENT13,
		GL_COLOR_ATTACHMENT14
};

class Framebuffer {
private:
	GLuint m_idFBO;
	GLuint m_idRBO;

	GLuint m_width;
	GLuint m_height;
	GLenum m_type; // GL_RGBA, GL_DEPTH_COMPONENT etc.

	unsigned int m_colattach;

public:
	Framebuffer( GLuint, GLuint );
	Framebuffer( GLuint, GLuint, GLenum );
	~Framebuffer();
	void bind();
	void unbind();
	void attachTexture( Texture& );
	void attachDepthTexture( Texture& );
	bool good();
	inline GLuint getId() { return m_idFBO; };
};

}

#endif // FRAMEBUFFER_H