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
    m_positionTexture = new Texture( cfg::screenwidth, cfg::screenheight, GL_RGBA32F, GL_FLOAT );
    m_normalTexture   = new Texture( cfg::screenwidth, cfg::screenheight, GL_RGBA16F, GL_FLOAT );
    m_colorTexture    = new Texture( cfg::screenwidth, cfg::screenheight, GL_RGBA, GL_UNSIGNED_BYTE );
    m_randomTexture   = new Texture( "assets/random.tga" );

    // init framebuffer
    m_framebuffer     = new Framebuffer( cfg::screenwidth, cfg::screenheight, GL_DEPTH_COMPONENT24 );

    // attach textures
	m_framebuffer->attachDepthTexture( *m_depthTexture );
	m_framebuffer->attachTexture( *m_positionTexture );
    m_framebuffer->attachTexture( *m_normalTexture );
	m_framebuffer->attachTexture( *m_colorTexture );

    // TODO: these two lines are counter intuitive
    GLenum drawBuffers[4] = { GL_NONE, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers( 4, drawBuffers );

    // final check
    if( !m_framebuffer->good() ) {
    	g_AceLog.setError( "GBuffer initialization failed." );
    	return;
    }

    // post processing preparations
    m_postprocessingTexture     = new Texture( cfg::screenwidth, cfg::screenheight, GL_RGBA32F, GL_FLOAT );
    m_postprocessingFramebuffer = new Framebuffer( cfg::screenwidth, cfg::screenheight );
    m_postprocessingFramebuffer->attachTexture( *m_postprocessingTexture );

    if( !m_postprocessingFramebuffer->good() ) {
        g_AceLog.setError( "Postprocessing framebuffer initialization failed." );
        return;
    }

    // shadow mapping 
    // int size = 512;
    // m_shadowmappingTexture     = new Texture( size, size, GL_DEPTH_COMPONENT, GL_FLOAT );
    // m_shadowmappingFramebuffer = new Framebuffer( size, size );
    // m_shadowmappingFramebuffer->attachDepthTexture( *m_shadowmappingTexture );

    // if( !m_shadowmappingFramebuffer->good() ) {
    //     g_AceLog.setError( "Shadowmapping framebuffer initialization failed." );
    //     return;
    // }

    // everything went well: load shader
    m_renderShader         = new Shader( "assets/shader/gbuffer_render.shader" );
    m_recShader            = new Shader( "assets/shader/gbuffer_record.shader" );
    m_postprocessingShader = new Shader( "assets/shader/post_processing.shader" );
    m_shadowmappingShader  = new Shader( "assets/shader/shadow_mapping.shader" );

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
    if( m_debugMode > 5 ) m_debugMode = 0;
}

void GBuffer::populate() {
    Ace *a = Ace::getEngine();
    startRecording();
        a->renderScene( *m_recShader );
    stopRecording();   
}

void GBuffer::render() {
    // fill the gbuffer
    populate();

    // render to screen quad
    m_postprocessingFramebuffer->bind();
        // shadowpass();
        illuminationpass();
    m_postprocessingFramebuffer->unbind();

    m_depthTexture->bind();
    m_colorTexture->bind();
    m_positionTexture->bind();
    m_normalTexture->bind();
    m_postprocessingTexture->bind();

    // apply postprocessing shader 
    m_postprocessingShader->bind();
        m_postprocessingShader->addUniform( "depthTexture", m_depthTexture->getId() );
        m_postprocessingShader->addUniform( "positionTexture", m_positionTexture->getId() );
        m_postprocessingShader->addUniform( "normalTexture", m_normalTexture->getId());
        m_postprocessingShader->addUniform( "colorTexture", m_colorTexture->getId() );

        m_postprocessingShader->addUniform( "tex", m_postprocessingTexture->getId() );
        m_postprocessingShader->addAttribute( "vertPos_modelspace", cfg::ACE_ATTRIB_VERT );

        m_postprocessingShader->addUniform( "screenwidth", cfg::screenwidth );
        m_postprocessingShader->addUniform( "screenheight", cfg::screenheight );

        m_renderQuad->draw();
    m_postprocessingShader->unbind();
}

void GBuffer::shadowpass() {
    // Ace *a    = Ace::getEngine();
    // Camera *o = Camera::getActive();

    // m_shadowmappingTexture->bind();
    // m_shadowmappingFramebuffer->bind();

    // for( auto l : a->Scene()->getLights() ) {
    //     glm::vec3 dir( 0, 0, -1 );
    //     glm::vec3 up( 0, 1, 0 );
    //     Camera c( l->getPosition(), dir, up, 0, 10, 0, 10, 1.0f, 1000.0f );

    //     a->renderScene( *m_shadowmappingShader );
    // }

    // m_shadowmappingFramebuffer->unbind();

    // o->setActive();
}

void GBuffer::illuminationpass() {
    Ace *a = Ace::getEngine();

	glViewport( 0, 0, cfg::screenwidth, cfg::screenheight );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	m_depthTexture->bind();
    m_colorTexture->bind();
    m_positionTexture->bind();
    m_normalTexture->bind();
    m_randomTexture->bind();
    
    m_renderShader->bind();
        // bind camera uniforms
        Camera* cam = Camera::getActive();

        m_renderShader->addUniform( "model", cam->getModelMatrix() );
        m_renderShader->addUniform( "proj", cam->getProjectionMatrix() );
        m_renderShader->addUniform( "view", cam->getViewMatrix() );
        m_renderShader->addUniform( "debug", float( m_debugMode ) );

        // set input variables
        m_renderShader->addUniform( "depthTexture", m_depthTexture->getId() );
        m_renderShader->addUniform( "positionTexture", m_positionTexture->getId() );
        m_renderShader->addUniform( "normalTexture", m_normalTexture->getId());
        m_renderShader->addUniform( "colorTexture", m_colorTexture->getId() );

        m_renderShader->addAttribute( "vertPos_modelspace", cfg::ACE_ATTRIB_VERT );
        m_renderShader->addAttribute( "in_uv", cfg::ACE_ATTRIB_UV );

        // pass lights to the shader
        int i = 0;
        glm::vec3 light_positions[100];
        glm::vec3 light_colors[100];
        float light_intensity[100];
        float light_radius[100];
        for( auto l : a->Scene()->getLights() ) {
            light_positions[i] = l->getPosition();
            light_colors[i]    = l->getColor();
            light_radius[i]    = l->getRadius();
            light_intensity[i] = l->getIntensity();
            ++i;
        }
        m_renderShader->addUniform( "light_count", float( i ) );
        m_renderShader->addUniformArray( "light_pos", i, light_positions );
        m_renderShader->addUniformArray( "light_color", i, light_colors );
        m_renderShader->addUniformArray( "light_intensity", i, light_intensity );
        m_renderShader->addUniformArray( "light_radius", i, light_radius );

        m_renderShader->addUniform( "screenwidth", cfg::screenwidth );
        m_renderShader->addUniform( "screenheight", cfg::screenheight );
        m_renderShader->addUniform( "randomTexture", m_randomTexture->getId() );

        // draw gbuffer quad
        m_renderQuad->draw();
    m_renderShader->unbind();

    m_depthTexture->unbind();
    m_colorTexture->unbind();
    m_positionTexture->unbind();
    m_normalTexture->unbind();
}

}
