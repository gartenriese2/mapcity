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
	m_fbo->createColorTexture(m_gbufferShadowTexture, GL_RGB32F, 2048, 2048);
	m_fbo->error();
	m_fbo->unbind();

	m_simpleShader = std::make_shared<Shader>("../shader/SimpleVert.shader", "../shader/SimpleFrag.shader");
	m_MVP_simplePass = m_simpleShader->addUniform("MVP");
	m_Light_simplePass = m_simpleShader->addUniform("Light");

	m_depthShader = std::make_shared<Shader>("../shader/DepthVert.shader", "../shader/DepthFrag.shader");
	m_MVP_depthPass = m_depthShader->addUniform("MVP");
	m_depthTextureWidth = 2048;
	m_depthTextureHeight = 2048;


	m_lightCam = std::make_shared<Camera>(glm::vec3(400.f, 100.f, -400.f), glm::vec3(-1.f, -1.f, 1.f), glm::vec3(0.f, 1.f, 0.f),
        						45.f, 1024, 1024, 0.1f, 10000.f);
	m_shadowShader = std::make_shared<Shader>("../shader/ShadowVert.shader", "../shader/ShadowFrag.shader");
	m_shadowBiasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	m_gbufferShader = std::make_shared<Shader>("../shader/GBufferVert.shader", "../shader/GBufferFrag.shader");
	m_MVP_gbufferPass = m_gbufferShader->addUniform("MVP");
	m_depthBiasMVP_gbufferPass = m_gbufferShader->addUniform("DepthBiasMVP");
	m_Light_gbufferPass = m_gbufferShader->addUniform("Light");
	m_gbufferShader->addUniformTexture(GL_TEXTURE_2D, m_gbufferShadowTexture, "shadowMap");

	m_simpleTexShader = std::make_shared<Shader>("../shader/SimpleTexVert.shader", "../shader/SimpleTexFrag.shader");
	vectorVec3 v = { glm::vec3(-1,-1,0), glm::vec3(-1,1,0), glm::vec3(1,1,0), glm::vec3(1,-1,0) };
	m_screenSizedQuad = PolygonObject(v, glm::vec3(0,0,0));
	m_simpleTexShader->addUniformTexture(GL_TEXTURE_2D, m_gbufferColorTexture, "texColor");
	m_simpleTexShader->addUniformTexture(GL_TEXTURE_2D, m_gbufferNormalTexture, "texNormal");
	m_simpleTexShader->addUniformTexture(GL_TEXTURE_2D, m_gbufferDepthTexture, "texDepth");
	m_simpleTexShader->addUniformTexture(GL_TEXTURE_2D, m_gbufferShadowTexture, "texShadow");
	m_projMat = m_simpleTexShader->addUniform("ProjMat");
	


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

	ObjectContainer::instance().emptyCuboidQueue();
	for (auto o : ObjectContainer::instance().getCuboids()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
		
	}

}

void Render::gbufferPass(const Camera &cam) const {

	m_fbo->bind();
	glViewport(0,0,2048,2048);

	GLenum db[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_NONE};
	glDrawBuffers(5, db);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gbufferShader->Use();

	m_gbufferShader->linkTextures();

	ObjectContainer::instance().emptyHexagonQueue();
	for (auto o : ObjectContainer::instance().getHexagons()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthMVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthBiasMVP = m_shadowBiasMatrix * depthMVP;
		m_gbufferShader->link(m_MVP_gbufferPass, MVP);
		m_gbufferShader->link(m_depthBiasMVP_gbufferPass, depthBiasMVP);
		m_gbufferShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	glDisable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyZoneQueue();
	for (auto o : ObjectContainer::instance().getZones()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthMVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthBiasMVP = m_shadowBiasMatrix * depthMVP;
		m_gbufferShader->link(m_MVP_simplePass, MVP);
		m_gbufferShader->link(m_depthBiasMVP_gbufferPass, depthBiasMVP);
		m_gbufferShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	ObjectContainer::instance().emptyPathQueue();
	for (auto o : ObjectContainer::instance().getPaths()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthMVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthBiasMVP = m_shadowBiasMatrix * depthMVP;
		m_gbufferShader->link(m_MVP_simplePass, MVP);
		m_gbufferShader->link(m_depthBiasMVP_gbufferPass, depthBiasMVP);
		m_gbufferShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}
	// glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glEnable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyCuboidQueue();
	for (auto o : ObjectContainer::instance().getCuboids()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthMVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::mat4 depthBiasMVP = m_shadowBiasMatrix * depthMVP;
		m_gbufferShader->link(m_MVP_simplePass, MVP);
		m_gbufferShader->link(m_depthBiasMVP_gbufferPass, depthBiasMVP);
		m_gbufferShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	m_fbo->unbind();
	glViewport(0,0,1024,1024);

}

void Render::gbufferClickPass(const Camera &cam, const unsigned int posX, const unsigned int posY, const bool infoMode) const {

	m_fbo->bind();
	glViewport(0,0,2048,2048);

	GLenum db[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
	glDrawBuffers(4, db);
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

	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	ObjectContainer::instance().emptyPathQueue();
	for (auto o : ObjectContainer::instance().getPaths()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}
	// glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glEnable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyCuboidQueue();
	for (auto o : ObjectContainer::instance().getCuboids()) {

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o.second.getModelMatrix();
		m_simpleShader->link(m_MVP_simplePass, MVP);
		m_simpleShader->link(m_Light_simplePass, 500.f, 600.f, 0.f);

		o.second.draw();
	}

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	GLfloat pix[] = { 0.f, 0.f, 0.f };
	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
	glReadPixels(posX * 2, (1024 - posY) * 2, 1, 1, GL_RGB, GL_FLOAT, pix);
	
	std::cout << "info mode? " << infoMode << "\n";
	if (infoMode) {
		InputHandler::instance().addQuery(glm::vec3(pix[0], pix[1], pix[2]));
	} else {
		InputHandler::instance().addZonePoint(glm::vec3(pix[0], pix[1], pix[2]));
	}

	m_fbo->unbind();
	glViewport(0,0,1024,1024);

}

void Render::simpleTexPass(const Camera &cam) const {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_simpleTexShader->Use();

	m_simpleTexShader->linkTextures();
	m_simpleTexShader->link(m_projMat, cam.getProjMat());

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

void Render::depthLightPass(const Camera &cam) const {

	m_fbo->bind();
	glViewport(0, 0, m_depthTextureWidth, m_depthTextureHeight);

	GLenum db[] = {GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_COLOR_ATTACHMENT4};
	glDrawBuffers(5, db);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_depthShader->Use();

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0f, 4.0f);

	// DRAW OBJECTS
	ObjectContainer::instance().emptyHexagonQueue();
	for (auto o : ObjectContainer::instance().getHexagons()) {

		// glm::mat4 MVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::vec3 lightInvDir = glm::vec3(400.f,100.f,-400.f);
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-100.f,100.f,-100.f,100.f,0.1f,1000.f);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(200.f,0.f,-200.f), glm::vec3(0.f,1.f,0.f));
		glm::mat4 MVP = depthProjectionMatrix * depthViewMatrix * o.second.getModelMatrix();
		m_depthShader->link(m_MVP_depthPass, MVP);

		o.second.draw();
	}

	glDisable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyZoneQueue();
	for (auto o : ObjectContainer::instance().getZones()) {

		// glm::mat4 MVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::vec3 lightInvDir = glm::vec3(400.f,100.f,-400.f);
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-100.f,100.f,-100.f,100.f,0.1f,1000.f);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(200.f,0.f,-200.f), glm::vec3(0.f,1.f,0.f));
		glm::mat4 MVP = depthProjectionMatrix * depthViewMatrix * o.second.getModelMatrix();
		m_depthShader->link(m_MVP_depthPass, MVP);

		o.second.draw();
	}

	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	ObjectContainer::instance().emptyPathQueue();
	for (auto o : ObjectContainer::instance().getPaths()) {

		// glm::mat4 MVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::vec3 lightInvDir = glm::vec3(400.f,100.f,-400.f);
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-100.f,100.f,-100.f,100.f,0.1f,1000.f);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(200.f,0.f,-200.f), glm::vec3(0.f,1.f,0.f));
		glm::mat4 MVP = depthProjectionMatrix * depthViewMatrix * o.second.getModelMatrix();
		m_depthShader->link(m_MVP_depthPass, MVP);

		o.second.draw();
	}
	// glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glEnable(GL_DEPTH_TEST);

	ObjectContainer::instance().emptyCuboidQueue();
	for (auto o : ObjectContainer::instance().getCuboids()) {

		// glm::mat4 MVP = m_lightCam->getProjMat() * m_lightCam->getViewMat() * o.second.getModelMatrix();
		glm::vec3 lightInvDir = glm::vec3(400.f,100.f,-400.f);
		glm::mat4 depthProjectionMatrix = glm::ortho<float>(-100.f,100.f,-100.f,100.f,0.1f,1000.f);
		glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(200.f,0.f,-200.f), glm::vec3(0.f,1.f,0.f));
		glm::mat4 MVP = depthProjectionMatrix * depthViewMatrix * o.second.getModelMatrix();
		m_depthShader->link(m_MVP_depthPass, MVP);

		o.second.draw();
	}

	glDisable(GL_POLYGON_OFFSET_FILL);

    m_fbo->unbind();
    glViewport(0, 0, cam.getWidth(), cam.getHeight());

}

void Render::shadowPass(const Camera &cam) const {

}