#include "gbufferrender.hpp"

GBufferRender::GBufferRender(Camera & cam)
  : m_cam(cam),
  	m_colorTex(cam.getWidth(), cam.getHeight()),
  	m_depthTex(cam.getWidth(), cam.getHeight(), GL_R32F),
  	m_normalTex(cam.getWidth(), cam.getHeight(), GL_RGB32F),
  	m_positionTex(cam.getWidth(), cam.getHeight(), GL_RGB32F),
  	m_depthAttachment(cam.getWidth(), cam.getHeight(), GL_DEPTH_COMPONENT32F)
{

	m_fbo.attachColorTexture(m_colorTex);
	m_fbo.attachColorTexture(m_depthTex);
	m_fbo.attachColorTexture(m_normalTex);
	m_fbo.attachColorTexture(m_positionTex);
	m_fbo.attachDepthTexture(m_depthAttachment);

}

void GBufferRender::draw() {

	m_gbufferPass.draw(m_cam, m_fbo);

	m_fbo.blit(GL_COLOR_ATTACHMENT0, 0, 0, static_cast<GLint>(m_cam.getWidth()),
		static_cast<GLint>(m_cam.getHeight()), 0, static_cast<GLint>(m_cam.getHeight()) / 2,
		static_cast<GLint>(m_cam.getWidth()) / 2, static_cast<GLint>(m_cam.getHeight()));

	m_fbo.blit(GL_COLOR_ATTACHMENT1, 0, 0, static_cast<GLint>(m_cam.getWidth()),
		static_cast<GLint>(m_cam.getHeight()), static_cast<GLint>(m_cam.getWidth()) / 2,
		static_cast<GLint>(m_cam.getHeight()) / 2, static_cast<GLint>(m_cam.getWidth()),
		static_cast<GLint>(m_cam.getHeight()));

	m_fbo.blit(GL_COLOR_ATTACHMENT2, 0, 0, static_cast<GLint>(m_cam.getWidth()), 
		static_cast<GLint>(m_cam.getHeight()), 0, 0, static_cast<GLint>(m_cam.getWidth()) / 2,
		static_cast<GLint>(m_cam.getHeight()) / 2);

	m_fbo.blit(GL_COLOR_ATTACHMENT3, 0, 0, static_cast<GLint>(m_cam.getWidth()), 
		static_cast<GLint>(m_cam.getHeight()), static_cast<GLint>(m_cam.getWidth()) / 2, 0, 
		static_cast<GLint>(m_cam.getWidth()), static_cast<GLint>(m_cam.getHeight()) / 2);

}

void GBufferRender::changeBaseSize(unsigned int w, unsigned int h) {

	m_cam.resize(w, h);

	m_colorTex.resize(w, h);
	m_depthTex.resize(w, h);
	m_normalTex.resize(w, h);
	m_positionTex.resize(w, h);
	m_depthAttachment.resize(w, h);

	glNamedFramebufferTexture(m_fbo, GL_COLOR_ATTACHMENT0 + 0, m_colorTex, 0);
	glNamedFramebufferTexture(m_fbo, GL_COLOR_ATTACHMENT0 + 1, m_depthTex, 0);
	glNamedFramebufferTexture(m_fbo, GL_COLOR_ATTACHMENT0 + 2, m_normalTex, 0);
	glNamedFramebufferTexture(m_fbo, GL_COLOR_ATTACHMENT0 + 3, m_positionTex, 0);
	glNamedFramebufferTexture(m_fbo, GL_DEPTH_ATTACHMENT, m_depthAttachment, 0);

	m_fbo.checkError();

}
