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
	m_depthTextureWidth = 1024;
	m_depthTextureHeight = 1024;


}

void Render::simplePass(Camera &cam) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_simpleShader->Use();

	for (std::vector<Object>::iterator o = m_world->getObjects().begin(); o != m_world->getObjects().end(); o++) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o->getModelMatrix();
		m_simpleShader->linkMatrix4f(m_MVP_simplePass, MVP);
		m_simpleShader->link3f(m_Light_simplePass, 500.f, 600.f, 0.f);

		o->draw();

	}

}

void Render::depthPlayerPass(Camera &cam) {

	m_fbo->bind();
    glViewport(0, 0, m_depthTextureWidth, m_depthTextureHeight);

    glClear(GL_DEPTH_BUFFER_BIT);

    m_depthShader->Use();

    for (std::vector<Object>::iterator o = m_world->getObjects().begin(); o != m_world->getObjects().end(); o++) {

    	glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o->getModelMatrix();
    	m_depthShader->linkMatrix4f(m_MVP_depthPass, MVP);

    	o->draw();

    }

    m_fbo->unbind();
    glViewport(0, 0, cam.getWidth(), cam.getHeight());

}

void Render::depthLightPass(Camera &cam) {

	m_fbo->bind();
	glViewport(0, 0, m_depthTextureWidth, m_depthTextureHeight);

}