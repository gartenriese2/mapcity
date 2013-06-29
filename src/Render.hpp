#ifndef RENDER_HPP
#define RENDER_HPP

#include "ogl.h"
#include "World.hpp"
#include "Shader.hpp"
#include "Fbo.hpp"
#include "Object.hpp"
#include <iostream>
#include <memory>

class Render {
public:
	Render(std::shared_ptr<World>);
	~Render();

	void init();
	void simplePass(Camera &);
	void gbufferPass(Camera &);
	void simpleTexPass();
	void depthPlayerPass(Camera &);
	void depthLightPass(Camera &);
	void shadowPass(Camera &);
	
private:
	std::shared_ptr<World> m_world;
	std::shared_ptr<Fbo> m_fbo;

	std::shared_ptr<Shader> m_simpleShader;
	GLuint m_MVP_simplePass;
	GLuint m_Light_simplePass;

	std::shared_ptr<Shader> m_depthShader;
	GLuint m_MVP_depthPass;
	int m_depthTextureWidth;
	int m_depthTextureHeight;
	std::shared_ptr<Camera> m_lightCam;

	std::shared_ptr<Shader> m_shadowShader;
	GLuint m_MVP_shadowPass;
	GLuint m_depthMVP_shadowPass;
	GLuint m_shadowTexture;

	std::shared_ptr<Shader> m_gbufferShader;
	GLuint m_MVP_gbufferPass;
	GLuint m_Light_gbufferPass;
	GLuint m_gbufferPositionTexture;
	GLuint m_gbufferNormalTexture;
	GLuint m_gbufferDepthTexture;
	GLuint m_gbufferColorTexture;

	std::shared_ptr<Shader> m_simpleTexShader;
	Object m_screenSizedQuad;

};

#endif
