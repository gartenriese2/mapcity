/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef GBUFFER_H
#define GBUFFER_H

#include "ogl.h"
#include "stl.h"

// Libace
#include "framebuffer.h"
#include "libace.h"

namespace ace {

class GBuffer {
private:
	Mesh* 			m_renderQuad;

	Texture*		m_depthTexture;
	Texture*		m_colorTexture;
	Texture*		m_normalTexture;
	Texture*		m_positionTexture;
	Texture*		m_randomTexture;
	Texture*		m_postprocessingTexture;
	// Texture*		m_shadowmappingTexture;

	Framebuffer* 	m_framebuffer;
	Framebuffer*	m_postprocessingFramebuffer;
	// Framebuffer*    m_shadowmappingFramebuffer;

	Shader*			m_renderShader;
	Shader*			m_recShader;
	Shader*			m_postprocessingShader;
	Shader*			m_shadowmappingShader;

	int 			m_debugMode;

    GBuffer();
    GBuffer( const GBuffer& ) {};

public:
	static GBuffer* getGBuffer();

	inline Shader* getRecShader() { return m_recShader; };

	void startRecording();
	void stopRecording();
	void illuminationpass();
	void shadowpass();
	void render();
	void populate();
	void nextDebugMode();
	~GBuffer();
};

}

#endif // GBUFFER_H