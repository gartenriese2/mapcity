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

	Framebuffer* 	m_framebuffer;

	Shader*			m_shader;
	Shader*			m_recShader;

	int 			m_debugMode;

    GBuffer();
    GBuffer( const GBuffer& ) {};

public:
	static GBuffer* getGBuffer();

	inline Shader* getRecShader() { return m_recShader; };

	void startRecording();
	void stopRecording();
	void render();
	void nextDebugMode();
	~GBuffer();
};

}

#endif // GBUFFER_H