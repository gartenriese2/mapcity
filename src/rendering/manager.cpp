#include "manager.hpp"

#include <MonoEngine/core/camera.hpp>
#include <MonoEngine/gl/shader.hpp>

#include <MonoEngine/core/log.hpp>

Manager::Manager(core::Camera & cam)
  : m_cam{cam},
	m_prog{"Street prog"},
	m_ibo{"Street ibo"},
	m_vao{"Street vao"},
	m_modelMatrixBuffer{"Street ssbo"}
{
	gl::Shader vert("shader/geometries/quad.vert", "quad_instance_vert");
	gl::Shader frag("shader/test/color.frag", "color_frag");
	m_prog.attachShader(vert);
	m_prog.attachShader(frag);

	// ibo
	std::vector<GLubyte> idx = {
		3, 2, 0,
		0, 1, 3
	};
	m_ibo.createImmutableStorage(static_cast<unsigned int>(idx.size() * sizeof(GLubyte)),
			0, idx.data());

	// vao
	m_vao.bind();
	m_vao.bindElementBuffer(m_ibo);
	m_vao.unbind();

	// modelMatrixBuffer
	m_modelMatrixBuffer.createImmutableStorage(1000	* static_cast<unsigned int>(sizeof(glm::mat4)),
			GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
}

void Manager::draw() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	m_prog.use();
	m_prog["col"] = glm::vec3{1.f, 1.f, 0.f};
	m_prog["ViewProj"] = m_cam.getProjMatrix() * m_cam.getViewMatrix();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_modelMatrixBuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0,
			static_cast<GLsizei>(m_streets.size()));
}

void Manager::addStreet(const std::shared_ptr<Drawable> & drawable) {
	m_streets.emplace_back(drawable);
	m_modelMatrixBuffer.setData((static_cast<unsigned int>(m_streets.size()) - 1) * sizeof(glm::mat4),
			sizeof(glm::mat4), glm::value_ptr(drawable->getModelMatrix()));
}
