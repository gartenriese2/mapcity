#include "basiclightingpass.hpp"

#include "../objects/objectinterface.hpp"
#include "../debug.hpp"
#include "../light.hpp"
#include "../handler.hpp"

BasicLightingPass::BasicLightingPass() {

	Shader vert(k_dir + "basic.vert");
	Shader frag(k_dir + "basiclighting.frag");
	m_program.attachShader(vert);
	m_program.attachShader(frag);

	m_lightBuffer.bindTo(0);

}

void BasicLightingPass::draw(const Camera & cam, const std::vector<std::shared_ptr<Light>> lights) {

	glViewport(0, 0, static_cast<GLsizei>(cam.getWidth()), static_cast<GLsizei>(cam.getHeight()));

	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	m_program.use();

	size_t size = lights.size();
	std::vector<LightData> data;
	for (const auto & light : lights) {
		data.emplace_back(light->getData());
	}	
	m_lightBuffer.addData(data, static_cast<unsigned int>(size));

	for (auto id : m_objects) {

		// vertex
		m_program["MVP"] = cam.getProjMat() * cam.getViewMat() * ObjectInterface::getModelMatrix(id);
		m_program["MV_IT"] = glm::inverse(glm::transpose(cam.getViewMat() * ObjectInterface::getModelMatrix(id)));
		m_program["M_IT"] = glm::inverse(glm::transpose(ObjectInterface::getModelMatrix(id)));
		m_program["M"] = ObjectInterface::getModelMatrix(id);

		// fragment
		m_program["camPos"] = cam.getPos();
		m_program["viewDir"] = cam.getDir();
		m_program["lightDataSize"] = static_cast<int>(size);
		m_program["material.emission"] = ObjectID::getID(id)->getEmission();
		m_program["material.ambient"] = ObjectID::getID(id)->getAmbient();
		m_program["material.diffuse"] = ObjectID::getID(id)->getDiffuse();
		m_program["material.specular"] = ObjectID::getID(id)->getSpecular();
		m_program["material.shininess"] = ObjectID::getID(id)->getShininess();

		ObjectInterface::draw(id);

	}

}
