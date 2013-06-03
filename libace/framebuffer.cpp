/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "framebuffer.h"

namespace ace {

Framebuffer::Framebuffer( GLuint width, GLuint height ) {
	m_idFBO     = 0;
	m_idRBO     = 0;
	m_colattach = 0;
	m_width     = width;
	m_height    = height;
	m_type      = GL_DEPTH_COMPONENT;

	glGenFramebuffers( 1, &m_idFBO );
	glBindFramebuffer( GL_FRAMEBUFFER, m_idFBO );
	glGenRenderbuffers( 1, &m_idRBO );
	glBindRenderbuffer( GL_RENDERBUFFER, m_idRBO );

	glRenderbufferStorage( GL_RENDERBUFFER, m_type, m_width, m_height );
}

Framebuffer::Framebuffer( GLuint width, GLuint height, GLenum type ) {
	m_idFBO     = 0;
	m_idRBO     = 0;
	m_colattach = 0;
	m_width     = width;
	m_height    = height;
	m_type      = type;
	
	glGenFramebuffers( 1, &m_idFBO );
	glBindFramebuffer( GL_FRAMEBUFFER, m_idFBO );
	glGenRenderbuffers( 1, &m_idRBO );
	glBindRenderbuffer( GL_RENDERBUFFER, m_idRBO );

	glRenderbufferStorage( GL_RENDERBUFFER, m_type, m_width, m_height );
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_idRBO );
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffers( 1, &m_idFBO );
	glDeleteRenderbuffers( 1, &m_idRBO );
}

void Framebuffer::bind() {
	glBindFramebuffer( GL_FRAMEBUFFER, m_idFBO );
}

void Framebuffer::unbind() {
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void Framebuffer::attachTexture( Texture& tex ) {
	GLenum att = colorattachment[ m_colattach++ ];
	glFramebufferTexture2D( GL_FRAMEBUFFER, att, GL_TEXTURE_2D, tex.getId(), 0 );
	// GLenum drawBuffers[1] = { att };
 //    glDrawBuffers( 1, drawBuffers );
}

void Framebuffer::attachDepthTexture( Texture& tex ) {
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.getId(), 0 );
	   
	// glDrawBuffer( GL_NONE );
 //    glReadBuffer( GL_NONE );
}

bool Framebuffer::good() {
	std::string error;
	GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );

    switch( status )
    {
    case GL_FRAMEBUFFER_COMPLETE:
     	error =  "Framebuffer complete.";
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
     	error =  "Framebuffer incomplete: Attachment is NOT complete.";
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
     	error =  "Framebuffer incomplete: No image is attached to FBO.";
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
     	error =  "Framebuffer incomplete: Draw buffer.";
        break;

    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
     	error =  "Framebuffer incomplete: Read buffer.";
        break;

    case GL_FRAMEBUFFER_UNSUPPORTED:
     	error =  "Framebuffer incomplete: Unsupported by FBO implementation.";
        break;

    default:
     	error =  "Framebuffer incomplete: Unknown error.";
        break;
    }   

    if( status == GL_FRAMEBUFFER_COMPLETE ) {
    	return true;
    } else {
    	g_AceLog.setError( error );
    	return false;
    }
}

}
