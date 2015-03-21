#include "manager.hpp"

#include <MonoEngine/core/camera.hpp>
#include <MonoEngine/gl/shader.hpp>

#include <MonoEngine/core/log.hpp>

#ifdef LEGACY_MODE
constexpr auto k_uboBinding = 0u;
#else
constexpr auto k_maxNumObjects = 400u;
#endif

Manager::Manager(core::Camera & cam)
#ifdef LEGACY_MODE
  : m_cam{cam}
#else
  : m_cam{cam},
	m_prog{"Street prog"},
	m_ibo{"Street ibo"},
	m_vao{"Street vao"},
	m_modelMatrixBuffer{"Street ssbo"}
#endif
{
#ifdef LEGACY_MODE
	GLint maxBufferSize;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxBufferSize);
	maxBufferSize /= static_cast<GLint>(sizeof(glm::mat4));
	m_maxNumObjects = static_cast<unsigned int>(maxBufferSize);
	gl::Shader vert(GL_VERTEX_SHADER);
	vert.addSourceFromString("#version 330 core\n");
	vert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(maxBufferSize) + ";\n");
	vert.addSourceFromFile("shader/geometries/quad_legacy.vert");
	if (!vert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	gl::Shader frag("shader/test/color.frag");
#else
	gl::Shader vert("shader/geometries/quad.vert", "quad_instance_vert");
	gl::Shader frag("shader/test/color.frag", "color_frag");
#endif
	m_prog.attachShader(vert);
	m_prog.attachShader(frag);

	// ibo
	std::vector<GLubyte> idx = {
		3, 2, 0,
		0, 1, 3
	};
#ifdef LEGACY_MODE
	m_ibo.bind(GL_ARRAY_BUFFER);
	m_ibo.createMutableStorage(static_cast<unsigned int>(idx.size() * sizeof(GLushort)),
			GL_STATIC_DRAW, idx.data());
	m_ibo.unbind();
#else
	m_ibo.createImmutableStorage(static_cast<unsigned int>(idx.size() * sizeof(GLubyte)),
			0, idx.data());
#endif

	// vao
	m_vao.bind();
#ifdef LEGACY_MODE
	m_ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
#else
	m_vao.bindElementBuffer(m_ibo);
#endif
	m_vao.unbind();
#ifdef LEGACY_MODE
	m_ibo.unbind();
#endif

	// modelMatrixBuffer
#ifdef LEGACY_MODE
	m_modelMatrixBuffer.bind(GL_UNIFORM_BUFFER);
	m_modelMatrixBuffer.createMutableStorage(m_maxNumObjects * static_cast<unsigned int>(sizeof(glm::mat4)),
			GL_DYNAMIC_DRAW);
	m_modelMatrixBuffer.unbind();
#else
	m_modelMatrixBuffer.createImmutableStorage(k_maxNumObjects	* static_cast<unsigned int>(sizeof(glm::mat4)),
			GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
#endif
}

void Manager::draw() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	m_prog.use();
	m_prog["col"] = glm::vec3{1.f, 1.f, 0.f};
	m_prog["ViewProj"] = m_cam.getProjMatrix() * m_cam.getViewMatrix();

#ifdef LEGACY_MODE
	// ubo
	const auto index = glGetUniformBlockIndex(static_cast<GLuint>(m_prog), "ModelMatrixBuffer");
	glUniformBlockBinding(static_cast<GLuint>(m_prog), index, k_uboBinding);
	glBindBufferBase(GL_UNIFORM_BUFFER, k_uboBinding, m_modelMatrixBuffer);
#else
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_modelMatrixBuffer);
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0,
			static_cast<GLsizei>(m_streets.size()));
	m_vao.unbind();
}

void Manager::addStreet(const std::shared_ptr<Drawable> & drawable) {
	m_streets.emplace_back(drawable);
	const auto typeSize = static_cast<unsigned int>(sizeof(glm::mat4));
#ifdef LEGACY_MODE
	m_modelMatrixBuffer.bind(GL_UNIFORM_BUFFER);
	m_modelMatrixBuffer.setData((static_cast<unsigned int>(m_streets.size()) - 1) * typeSize,
			typeSize, glm::value_ptr(drawable->getModelMatrix()));
	m_modelMatrixBuffer.unbind();
#else
	m_modelMatrixBuffer.setData((static_cast<unsigned int>(m_streets.size()) - 1) * typeSize,
			typeSize, glm::value_ptr(drawable->getModelMatrix()));
#endif
}
