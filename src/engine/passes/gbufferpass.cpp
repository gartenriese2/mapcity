#include "gbufferpass.hpp"

#include "../camera.hpp"
#include "../objects/objectinterface.hpp"
#include "../gl/fbo.hpp"
#include "../debug.hpp"

GBufferPass::GBufferPass() {

	Shader vert(k_dir + "basic.vert");
	Shader frag(k_dir + "gbuffer.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

}

void GBufferPass::draw(const Camera & cam, const gl::FBO & fbo) {

	fbo.bind();

	glViewport(0, 0, static_cast<GLsizei>(cam.getWidth()), static_cast<GLsizei>(cam.getHeight()));

	GLenum db[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
	glDrawBuffers(4, db);

	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	m_program.use();

	for (auto id : m_objects) {

		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * ObjectInterface::getModelMatrix(id);
		m_program["MV_IT"] = glm::inverse(glm::transpose(cam.getViewMat() * ObjectInterface::getModelMatrix(id)));
		m_program["M_IT"] = glm::inverse(glm::transpose(ObjectInterface::getModelMatrix(id)));
		m_program["M"] = ObjectInterface::getModelMatrix(id);
		ObjectInterface::draw(id);

	}

	fbo.unbind();

}
