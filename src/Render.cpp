#include "Render.hpp"

Render::Render(World * world) {
	m_world = world;
}

Render::~Render() {

}

void Render::init() {
	
	m_fbo = new Fbo();

	m_simpleShader = new Shader("../shader/SimpleVert.shader", "../shader/SimpleFrag.shader");
	m_MVP_simplePass = m_simpleShader->addUniformMatrix4f("MVP");
	m_Light_simplePass = m_simpleShader->addUniform3f("Light");

	m_depthShader = new Shader("../shader/DepthVert.shader", "../shader/DepthFrag.shader");
	m_MVP_depthPass = m_depthShader->addUniformMatrix4f("MVP");
	m_depthTextureWidth = 2048;
	m_depthTextureHeight = 2048;
	m_fbo->bind();
	m_fbo->createDepthTexture(m_shadowTexture, 2048, 2048);
	m_fbo->unbind();

	m_lightCam = new Camera(glm::vec3(100,100,0), glm::vec3(-1,-1,0), glm::vec3(-1,1,0), 100, 100, 100, 100);
	m_shadowShader = new Shader("../shader/ShadowVert.shader", "../shader/ShadowFrag.shader");
	glm::mat4 m_shadowBiasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);


}

void Render::simplePass(Camera &cam) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_simpleShader->Use();

	for (auto o : m_world->getObjects()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.getModelMatrix();
		m_simpleShader->linkMatrix4f(m_MVP_simplePass, MVP);
		m_simpleShader->link3f(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.draw();

	}
}

void Render::depthPlayerPass(Camera &cam) {

	// m_fbo->bind();
 //    glViewport(0, 0, m_depthTextureWidth, m_depthTextureHeight);

    glClear(GL_DEPTH_BUFFER_BIT);

    m_depthShader->Use();

    for (auto o : m_world->getObjects()) {

    	glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.getModelMatrix();
    	m_depthShader->linkMatrix4f(m_MVP_depthPass, MVP);

    	o.draw();

    }

    // m_fbo->unbind();
    // glViewport(0, 0, cam.getWidth(), cam.getHeight());

}

void Render::depthLightPass(Camera &cam) {

	// m_fbo->bind();
	// glViewport(0, 0, m_depthTextureWidth, m_depthTextureHeight);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_depthShader->Use();

	for (auto o : m_world->getObjects()) {

    	glm::mat4 MVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.getModelMatrix();
    	m_depthShader->linkMatrix4f(m_MVP_depthPass, MVP);

    	o.draw();

    }

    // m_fbo->unbind();
    // glViewport(0, 0, cam.getWidth(), cam.getHeight());

}

void Render::shadowPass(Camera &cam) {

	
	

	// for (auto o : m_world->getObjects()) {

 //    	glm::mat4 depthMVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.getModelMatrix();
 //    	glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.getModelMatrix();
 //    	glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
    	
 //    	m_shadowShader->linkMatrix4f(m_BiasMVP_shadowPass, depthBiasMVP);
 //    	m_shadowShader->linkMatrix4f(m_MVP_shadowPass, MVP);

 //    	o.draw();

 //    }

}