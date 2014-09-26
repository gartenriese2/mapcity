#include "basicpass.hpp"

#include "../camera.hpp"
#include "../objects/objectinterface.hpp"
#include "../debug.hpp"

BasicPass::BasicPass() {

	Shader vert(k_dir + "basic.vert");
	Shader frag(k_dir + "basic.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

}

void BasicPass::draw(const Camera & cam) {

	glViewport(0, 0, static_cast<GLsizei>(cam.getWidth()), static_cast<GLsizei>(cam.getHeight()));

	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	for (auto id : m_objects) {

		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * ObjectInterface::getModelMatrix(id);
		ObjectInterface::draw(id);

	}

}
