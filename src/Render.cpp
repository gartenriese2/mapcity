#include "Render.hpp"

Render::Render() {
	
}

Render::~Render() {

}

void Render::init() {
	
	m_fbo = std::make_shared<Fbo>();
	m_fbo->bind();
	m_fbo->createDepthTexture(m_shadowTexture, 2048, 2048);
	m_fbo->createColorTexture(m_gbufferPositionTexture, GL_RGB32F, 2048, 2048);
	m_fbo->createColorTexture(m_gbufferNormalTexture, GL_RGB32F, 2048, 2048);
	m_fbo->createColorTexture(m_gbufferDepthTexture, GL_RGB32F, 2048, 2048);
	m_fbo->createColorTexture(m_gbufferColorTexture, GL_RGB32F, 2048, 2048);
	m_fbo->error();
	m_fbo->unbind();

	m_simpleShader = std::make_shared<Shader>("../shader/SimpleVert.shader", "../shader/SimpleFrag.shader");
	m_MVP_simplePass = m_simpleShader->addUniform("MVP");
	m_Light_simplePass = m_simpleShader->addUniform("Light");

	m_depthShader = std::make_shared<Shader>("../shader/DepthVert.shader", "../shader/DepthFrag.shader");
	m_MVP_depthPass = m_depthShader->addUniform("MVP");
	m_depthTextureWidth = 2048;
	m_depthTextureHeight = 2048;


	m_lightCam = std::make_shared<Camera>(glm::vec3(100,100,0), glm::vec3(-1,-1,0), glm::vec3(-1,1,0), 100, 100, 100, 100);
	m_shadowShader = std::make_shared<Shader>("../shader/ShadowVert.shader", "../shader/ShadowFrag.shader");
	glm::mat4 m_shadowBiasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	m_gbufferShader = std::make_shared<Shader>("../shader/GBufferVert.shader", "../shader/GBufferFrag.shader");
	m_MVP_gbufferPass = m_gbufferShader->addUniform("MVP");
	m_Light_gbufferPass = m_gbufferShader->addUniform("Light");

	m_simpleTexShader = std::make_shared<Shader>("../shader/SimpleTexVert.shader", "../shader/SimpleTexFrag.shader");
	m_screenSizedQuad = Object(ObjectType::QUAD, glm::vec3(-1,-1,0), glm::vec3(1,-1,0), glm::vec3(-1,1,0), glm::vec3(0,0,0));
	m_simpleTexShader->addUniformTexture(GL_TEXTURE_2D, m_gbufferPositionTexture, "tex");
	


}

void Render::simplePass(const Camera &cam) const {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_simpleShader->Use();
	
	ObjectContainer::instance().emptyHexagonQueue();
	for (auto o : ObjectContainer::instance().getHexagons()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	glDisable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyZoneQueue();
	for (auto o : ObjectContainer::instance().getZones()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	ObjectContainer::instance().emptyPathQueue();
	for (auto o : ObjectContainer::instance().getPaths()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	glEnable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyBuildingQueue();
	for (auto o : ObjectContainer::instance().getBuildings()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
		
	}

}

void Render::gbufferPass(const Camera &cam) const {

	// m_fbo->bind();

	// GLenum db[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
	// glDrawBuffers(4, db);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gbufferShader->Use();

	ObjectContainer::instance().emptyHexagonQueue();
	for (auto o : ObjectContainer::instance().getHexagons()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	glDisable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyZoneQueue();
	for (auto o : ObjectContainer::instance().getZones()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	
	ObjectContainer::instance().emptyPathQueue();
	for (auto o : ObjectContainer::instance().getPaths()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	glEnable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyBuildingQueue();
	for (auto o : ObjectContainer::instance().getBuildings()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	// m_fbo->unbind();

}

void Render::simpleTexPass() const {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_simpleTexShader->Use();

	m_simpleTexShader->linkTextures();

	m_screenSizedQuad.draw();
	
}

void Render::depthPlayerPass(const Camera &cam) const {

	m_fbo->bind();
    glViewport(0, 0, m_depthTextureWidth, m_depthTextureHeight);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_depthShader->Use();

    // DRAW OBJECTS

    m_fbo->unbind();
    glViewport(0, 0, cam.getWidth(), cam.getHeight());

    

}

// void Render::depthLightPass(const Camera &cam) const {

// 	// m_fbo->bind();
// 	// glViewport(0, 0, m_depthTextureWidth, m_depthTextureHeight);

// 	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

// 	m_depthShader->Use();

// 	// DRAW OBJECTS

//     // m_fbo->unbind();
//     // glViewport(0, 0, cam.getWidth(), cam.getHeight());

// }

// void Render::shadowPass(const Camera &cam) const {

// }