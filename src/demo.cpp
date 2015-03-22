#include "demo.hpp"

#include <MonoEngine/gl/shader.hpp>
#include <MonoEngine/core/log.hpp>
#include <MonoEngine/extern/imgui.h>

#include <chrono>
#include <random>

#ifdef LEGACY_MODE
constexpr auto k_initialNumObjects = 5u;
constexpr auto k_uboBinding = 0u;
#else
constexpr auto k_maxNumObjects = 400u;
constexpr auto k_initialNumObjects = 32u;
#endif
constexpr auto k_avg = 20u;

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0.f, 1.f);

Demo::Demo(const glm::uvec2 & size)
  : m_engine{size, "monoEngine Demo", true},
#ifndef LEGACY_MODE
	m_prog{"demo prog"},
	m_fbo{"demo fbo"},
	m_colorTex{"demo color tex"},
	m_depthTex{"demo depth tex"},
	m_vbo{"demo vbo"},
	m_ibo{"demo ibo"},
	m_modelMatrixBuffer{"demo ssbo"},
	m_vao{"demo vao"},
#endif
	m_numObjects{k_initialNumObjects}
{
	m_engine.showFPS(true);
	init(size);
}

void Demo::init(const glm::uvec2 & size) {

	m_cam.setRatio(static_cast<float>(size.x) / static_cast<float>(size.y));
	m_cam.setFov(glm::radians(45.f));
	m_cam.translate({0.f, 0.f, 3.f});

	// shader
#ifdef LEGACY_MODE
	GLint maxBufferSize;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxBufferSize);
	maxBufferSize /= static_cast<GLint>(sizeof(glm::mat4));
	m_maxNumObjects = static_cast<unsigned int>(std::sqrt(maxBufferSize));
	gl::Shader vert(GL_VERTEX_SHADER);
	vert.addSourceFromString("#version 330 core\n");
	vert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(maxBufferSize) + ";\n");
	vert.addSourceFromFile("shader/test/instancedraw_legacy.vert");
	if (!vert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	gl::Shader frag("shader/test/color_legacy.frag");
#else
	gl::Shader vert("shader/test/instancedraw.vert", "instance_vert");
	gl::Shader frag("shader/test/color.frag", "color_frag");
#endif
	m_prog.attachShader(vert);
	m_prog.attachShader(frag);

	// vbo (pos3 and norm3 interleaved)
	std::vector<GLfloat> vec = {
		-1.f, -1.f, 1.f,
		0.f, 0.f, 1.f,
		1.f, -1.f, 1.f,
		0.f, 0.f, 1.f,
		1.f, 1.f, 1.f,
		0.f, 0.f, 1.f,
		-1.f, 1.f, 1.f,
		0.f, 0.f, 1.f,

		-1.f, -1.f, -1.f,
		-1.f, 0.f, 0.f,
		-1.f, -1.f, 1.f,
		-1.f, 0.f, 0.f,
		-1.f, 1.f, 1.f,
		-1.f, 0.f, 0.f,
		-1.f, 1.f, -1.f,
		-1.f, 0.f, 0.f,

		1.f, -1.f, -1.f,
		0.f, 0.f, -1.f,
		-1.f, -1.f, -1.f,
		0.f, 0.f, -1.f,
		-1.f, 1.f, -1.f,
		0.f, 0.f, -1.f,
		1.f, 1.f, -1.f,
		0.f, 0.f, -1.f,

		1.f, -1.f, 1.f,
		1.f, 0.f, 0.f,
		1.f, -1.f, -1.f,
		1.f, 0.f, 0.f,
		1.f, 1.f, -1.f,
		1.f, 0.f, 0.f,
		1.f, 1.f, 1.f,
		1.f, 0.f, 0.f,

		-1.f, 1.f, 1.f,
		0.f, 1.f, 0.f,
		1.f, 1.f, 1.f,
		0.f, 1.f, 0.f,
		1.f, 1.f, -1.f,
		0.f, 1.f, 0.f,
		-1.f, 1.f, -1.f,
		0.f, 1.f, 0.f,

		1.f, -1.f, -1.f,
		0.f, -1.f, 0.f,
		-1.f, -1.f, -1.f,
		0.f, -1.f, 0.f,
		-1.f, -1.f, 1.f,
		0.f, -1.f, 0.f,
		1.f, -1.f, 1.f,
		0.f, -1.f, 0.f
	};
#ifdef LEGACY_MODE
	m_vbo.bind(GL_ARRAY_BUFFER);
	m_vbo.createMutableStorage(static_cast<unsigned int>(vec.size() * sizeof(GLfloat)),
			GL_STATIC_DRAW, vec.data());
	m_vbo.unbind();
#else
	m_vbo.createImmutableStorage(static_cast<unsigned int>(vec.size() * sizeof(GLfloat)),
			0, vec.data());
#endif

	// ibo
	std::vector<GLushort> idx = {
		 0,  1,  2,
		 2,  3,  0,

		 4,  5,  6,
		 6,  7,  4,

		 8,  9, 10,
		10, 11,  8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};
#ifdef LEGACY_MODE
	m_ibo.bind(GL_ARRAY_BUFFER);
	m_ibo.createMutableStorage(static_cast<unsigned int>(idx.size() * sizeof(GLushort)),
			GL_STATIC_DRAW, idx.data());
	m_ibo.unbind();
#else
	m_ibo.createImmutableStorage(static_cast<unsigned int>(idx.size() * sizeof(GLushort)),
			0, idx.data());
#endif

	// vao
	m_vao.bind();
#ifdef LEGACY_MODE
	m_vbo.bind(GL_ARRAY_BUFFER);
#endif
	m_vao.enableAttribBinding(0);
	m_vao.enableAttribBinding(1);
	m_vao.bindVertexBuffer(0, m_vbo, 0, 6 * sizeof(GLfloat));
	m_vao.bindVertexFormat(0, 0, 3, GL_FLOAT, GL_FALSE, 0);
	m_vao.bindVertexFormat(0, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
#ifdef LEGACY_MODE
	m_ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
	m_vao.unbind();
	m_vbo.unbind();
	m_ibo.unbind();
#else
	m_vao.bindElementBuffer(m_ibo);
#endif

	// keys
	m_engine.getInputPtr()->addKeyFunc([&](const int key, const int, const int action, const int mods){
		if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			if ((mods & GLFW_MOD_SHIFT) != 0) {
				m_cam.translateLocal({0.f, 0.f, -0.5f});
			} else {
				m_cam.translateLocal({0.f, 0.f, -0.05f});
			}
		}
		if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			if ((mods & GLFW_MOD_SHIFT) != 0) {
				m_cam.translateLocal({0.f, 0.f, 0.5f});
			} else {
				m_cam.translateLocal({0.f, 0.f, 0.05f});
			}
		}
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(m_engine.getWindowPtr()->getGLFWWindow(), GL_TRUE);
		}
	});

	// modelMatrixBuffer
#ifdef LEGACY_MODE
	m_modelMatrixBuffer.bind(GL_UNIFORM_BUFFER);
	m_modelMatrixBuffer.createMutableStorage(m_maxNumObjects * m_maxNumObjects
			* static_cast<unsigned int>(sizeof(glm::mat4)), GL_DYNAMIC_DRAW);
	m_objects.resize(m_maxNumObjects * m_maxNumObjects);
#else
	m_modelMatrixBuffer.createImmutableStorage(k_maxNumObjects * k_maxNumObjects * sizeof(glm::mat4),
			GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
	m_objects.resize(k_maxNumObjects * k_maxNumObjects);
#endif
	orderModels();
	setModelMatrices();
#ifdef LEGACY_MODE
	m_modelMatrixBuffer.unbind();
#endif

#ifdef LEGACY_MODE
	m_colorTex.bind();
#endif
	m_colorTex.createImmutableStorage(size.x, size.y, GL_RGBA32F);
#ifdef LEGACY_MODE
	m_depthTex.bind();
#endif
	m_depthTex.createImmutableStorage(size.x, size.y, GL_DEPTH_COMPONENT32F);
#ifdef LEGACY_MODE
	m_fbo.bind();
#endif
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT0, m_colorTex, 0);
	m_fbo.attachTexture(GL_DEPTH_ATTACHMENT, m_depthTex, 0);
#ifdef LEGACY_MODE
	if (!m_fbo.isComplete()) {
#else
	if (!m_fbo.isComplete(GL_FRAMEBUFFER)) {
#endif
		LOG_WARNING("demo has incomplete fbo!");
	}
#ifdef LEGACY_MODE
	m_fbo.unbind();
#endif

}

void Demo::orderModels() {
	const auto scale = 2.f / static_cast<float>(m_numObjects);
	auto i = 0u;
	for (auto & obj : m_objects) {
		obj.resetScale();
		obj.resetMoves();
		obj.scale({scale * 0.33f, scale * 0.33f, scale * 0.33f});
		const auto y = i / m_numObjects;
		const auto x = i % m_numObjects;
		obj.moveTo({-1.f + scale * (static_cast<float>(x) + 0.5f),
				-1.f + scale * (static_cast<float>(y) + 0.5f), 0.f});
		i++;
	}
}

void Demo::setModelMatrices() {
	void * voidPtr = m_modelMatrixBuffer.map(0, m_numObjects * m_numObjects, GL_MAP_WRITE_BIT);
	auto * ptr = reinterpret_cast<glm::mat4 *>(voidPtr);
	auto count = 0u;
	for (const auto & obj : m_objects) {
		*ptr = obj.getModelMatrix();
		++ptr;
		if (++count > m_numObjects * m_numObjects) break;
	}
	m_modelMatrixBuffer.unmap();
}

double Demo::getAverageMs(const std::deque<GLuint64> & deque) {
	auto avg = 0.0;
	for (const auto & t : deque) {
		avg += static_cast<double>(t) * 0.000001;
	}
	avg /= static_cast<double>(deque.size());
	return avg;
}

double Demo::getAverageMs(const std::deque<double> & deque) {
	auto avg = 0.0;
	for (const auto & t : deque) {
		avg += t;
	}
	avg /= static_cast<double>(deque.size());
	return avg;
}

bool Demo::render() {

	const auto start = std::chrono::system_clock::now();
	m_timer.start();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// setup shader
	m_prog.use();
	m_prog["col"] = glm::vec3{1.f, 0.f, 0.f};
	m_prog["ViewProj"] = m_cam.getProjMatrix() * m_cam.getViewMatrix();

#ifdef LEGACY_MODE
	// ubo
	const auto index = glGetUniformBlockIndex(static_cast<GLuint>(m_prog), "ModelMatrixBuffer");
	glUniformBlockBinding(static_cast<GLuint>(m_prog), index, k_uboBinding);
	glBindBufferBase(GL_UNIFORM_BUFFER, k_uboBinding, m_modelMatrixBuffer);
#else
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_modelMatrixBuffer);
#endif

	// draw
	m_fbo.bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_fbo.draw({GL_COLOR_ATTACHMENT0});
	m_vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0,
			static_cast<GLsizei>(m_numObjects * m_numObjects));
	m_fbo.unbind();
	m_vao.unbind();

#ifdef LEGACY_MODE
	m_fbo.bind(GL_READ_FRAMEBUFFER);
	glDrawBuffer(GL_BACK);
#endif
	const auto size = static_cast<glm::ivec2>(m_engine.getWindowPtr()->getFrameBufferSize());
	m_fbo.blitAttachment(GL_COLOR_ATTACHMENT0, {0, 0, size.x, size.y});
#ifdef LEGACY_MODE
	m_fbo.unbind();
#endif

	// rotate objects
	for (auto i = 0u; i < m_numObjects * m_numObjects; ++i) {
		m_objects[i].rotate(0.03f,
				{distribution(generator), distribution(generator), distribution(generator)});
		m_objects[i].rotateAround(0.01f, {0.f, 1.f, 0.f});
	}
#ifdef LEGACY_MODE
	m_modelMatrixBuffer.bind(GL_UNIFORM_BUFFER);
#endif
	setModelMatrices();
#ifdef LEGACY_MODE
	m_modelMatrixBuffer.unbind();
#endif

	// stop timer
	m_timeDeque.emplace_back(m_timer.stop());
	static auto ms = 0.0;
	if (m_timeDeque.size() == k_avg) {
		ms = getAverageMs(m_timeDeque);
		m_timeDeque.erase(m_timeDeque.begin(), m_timeDeque.begin() + k_avg / 2);
	}
	std::chrono::duration<double> tmp = std::chrono::system_clock::now() - start;
	m_cpuTimeDeque.emplace_back(tmp.count() * 1000.0);
	static auto ms_cpu = 0.0;
	if (m_cpuTimeDeque.size() == k_avg) {
		ms_cpu = getAverageMs(m_cpuTimeDeque);
		m_cpuTimeDeque.erase(m_cpuTimeDeque.begin(), m_cpuTimeDeque.begin() + k_avg / 2);
	}

	// Gui
	ImGui::NewFrame();
	ImGui::Begin("Demo");
	int numObj = static_cast<int>(m_numObjects);
#ifdef LEGACY_MODE
	ImGui::SliderInt("numObjects", &numObj, 1, static_cast<int>(m_maxNumObjects));
#else
	ImGui::SliderInt("numObjects", &numObj, 1, k_maxNumObjects);
#endif
	if (m_numObjects != static_cast<unsigned int>(numObj)) {
		m_numObjects = static_cast<unsigned int>(numObj);
		orderModels();
#ifdef LEGACY_MODE
		m_modelMatrixBuffer.bind(GL_UNIFORM_BUFFER);
#endif
		setModelMatrices();
#ifdef LEGACY_MODE
		m_modelMatrixBuffer.unbind();
#endif
	}
	ImGui::Columns(2, "time", true);
	ImGui::Text("ms gpu");
	ImGui::NextColumn();
	ImGui::Text("%f", ms);
	ImGui::NextColumn();
	ImGui::Text("ms cpu");
	ImGui::NextColumn();
	ImGui::Text("%f", ms_cpu);
	ImGui::NextColumn();
	ImGui::End();

	return m_engine.render();

}
