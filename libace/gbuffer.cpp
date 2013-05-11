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
    m_shader    = new Shader( "../libace/shader/gbuffer_render.shader" );
    m_recShader = new Shader( "../libace/shader/gbuffer_record.shader" );

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
    Ace *a = Ace::getEngine();

	glViewport( 0, 0, cfg::screenwidth, cfg::screenheight );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_depthTexture->bind();
    m_colorTexture->bind();
    m_positionTexture->bind();
    m_normalTexture->bind();
    
    m_shader->bind();
        // bind camera uniforms
        Camera* cam = Camera::getActive();

        m_shader->addUniform( "model", cam->getModelMatrix() );
        m_shader->addUniform( "proj", cam->getProjectionMatrix() );
        m_shader->addUniform( "view", cam->getViewMatrix() );
        m_shader->addUniform( "debug", float( m_debugMode ) );

        // set input variables
        m_shader->addUniform( "depthTexture", m_depthTexture->getId() );
        m_shader->addUniform( "positionTexture", m_positionTexture->getId() );
        m_shader->addUniform( "normalTexture", m_normalTexture->getId());
        m_shader->addUniform( "colorTexture", m_colorTexture->getId() );

        m_shader->addAttribute( "vertPos_modelspace", cfg::ACE_ATTRIB_VERT );
        m_shader->addAttribute( "in_uv", cfg::ACE_ATTRIB_UV );

        for( auto l : a->Scene()->getLights() ) {
            m_shader->addUniform( "light_pos", l->getPosition() );
            m_shader->addUniform( "light_radius", l->getRadius() );
        }

        // draw gbuffer quad
        m_renderQuad->draw();
    m_shader->unbind();

    m_depthTexture->unbind();
    m_colorTexture->unbind();
    m_positionTexture->unbind();
    m_normalTexture->unbind();

}

}
