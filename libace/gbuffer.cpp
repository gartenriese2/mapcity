/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "gbuffer.h"

namespace ace {

GBuffer::GBuffer() {
	// create quad to put the texture on it
	m_renderQuad = new Mesh();
    m_renderQuad->makeQuad();

    // check extension
    GLint maxbuffers;
    glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS, &maxbuffers );
    if( maxbuffers < 4 ) {
        g_AceLog.setError( "GBuffer initialization failed: multiple render targets not supported" );
        return;
    }

    // create Textures
    m_depthTexture    = new Texture( cfg::screenwidth, cfg::screenheight, GL_DEPTH_COMPONENT, GL_FLOAT );
    m_positionTexture = new Texture( cfg::screenwidth, cfg::screenheight, GL_RGBA, GL_FLOAT );
    m_normalTexture   = new Texture( cfg::screenwidth, cfg::screenheight, GL_RGBA, GL_FLOAT );
    m_colorTexture    = new Texture( cfg::screenwidth, cfg::screenheight, GL_RGBA, GL_UNSIGNED_BYTE );

    // init framebuffer
    m_framebuffer     = new Framebuffer( cfg::screenwidth, cfg::screenheight );

    // attach textures
	m_framebuffer->attachDepthTexture( *m_depthTexture );
	m_framebuffer->attachTexture( *m_positionTexture );
    m_framebuffer->attachTexture( *m_normalTexture );
	m_framebuffer->attachTexture( *m_colorTexture );

    GLenum drawBuffers[4] = { GL_NONE, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers( 4, drawBuffers );

    // final check
    if( !m_framebuffer->good() ) {
    	g_AceLog.setError( "GBuffer initialization failed." );
    	return;
    }

    // everything went well: load shader
    m_shader = new Shader();
    m_shader->load( "../shader/gbuffer_render.shader" );

    m_recShader = new Shader();
    m_recShader->load( "../shader/gbuffer_record.shader" );

    // turn off debug mode
    m_debugMode = 0;
}

GBuffer::~GBuffer() {

}

GBuffer* GBuffer::getGBuffer() {
    static GBuffer instance;
    return &instance;
}

void GBuffer::startRecording() {

    m_framebuffer->bind();
    m_recShader->bind();

    glViewport( 0, 0, cfg::screenwidth, cfg::screenheight );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}

void GBuffer::stopRecording() {

    m_recShader->unbind();
	m_framebuffer->unbind();

}

void GBuffer::nextDebugMode() {
    m_debugMode++;
    if( m_debugMode > 4 ) m_debugMode = 0;
}

void GBuffer::render() {
	int loc;

	glViewport( 0, 0, cfg::screenwidth, cfg::screenheight );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_depthTexture->bind();
    m_colorTexture->bind();
    m_positionTexture->bind();
    m_normalTexture->bind();
    
    m_shader->bind();
        // bind camera uniforms
        Camera* cam = Camera::getActive();

        loc = glGetUniformLocation( m_shader->getId(), "model" );
        glUniformMatrix4fv( loc, 1, GL_FALSE, glm::value_ptr( cam->getModelMatrix() ) ) ;

        loc = glGetUniformLocation( m_shader->getId(), "proj" );
        glUniformMatrix4fv( loc, 1, GL_FALSE, glm::value_ptr( cam->getProjectionMatrix() ) );
            
        loc = glGetUniformLocation( m_shader->getId(), "view" );
        glUniformMatrix4fv( loc, 1, GL_FALSE, glm::value_ptr( cam->getViewMatrix() ) );

        loc = glGetUniformLocation( m_shader->getId(), "debug" );
        glUniform1f( loc, float( m_debugMode ) );

        // set input variables
        loc = glGetUniformLocation( m_shader->getId(), "depthTexture" );
        glUniform1i( loc, m_depthTexture->getId() );    

        loc = glGetUniformLocation( m_shader->getId(), "positionTexture" );
        glUniform1i( loc, m_positionTexture->getId() );    

        loc = glGetUniformLocation( m_shader->getId(), "normalTexture" );
        glUniform1i( loc, m_normalTexture->getId() );    

        loc = glGetUniformLocation( m_shader->getId(), "colorTexture" );
        glUniform1i( loc, m_colorTexture->getId() );    

        glBindAttribLocation( m_shader->getId(), cfg::ACE_ATTRIB_VERT, "vertPos_modelspace" );
        glBindAttribLocation( m_shader->getId(), cfg::ACE_ATTRIB_UV, "in_uv" );

        m_renderQuad->draw();
    m_shader->unbind();

    m_depthTexture->unbind();
    m_colorTexture->unbind();
    m_positionTexture->unbind();
    m_normalTexture->unbind();

}

}
