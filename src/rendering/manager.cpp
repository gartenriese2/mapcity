#include "manager.hpp"

#include <MonoEngine/core/camera.hpp>
#include <MonoEngine/core/log.hpp>
#include <MonoEngine/gl/shader.hpp>

/**************************************************************************************************/

constexpr auto k_modelBufferBinding = 0u;
constexpr auto k_maxNumObjects = 400u;

/**************************************************************************************************/

Manager::Manager(core::Camera & cam, const glm::uvec2 & size)
  : m_cam{cam},
	m_screenSize{size},
  	m_maxNumObjects{k_maxNumObjects}
{
	GLint maxBufferSize;
#ifdef LEGACY_MODE
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxBufferSize);
#else
	glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &maxBufferSize);
#endif
	maxBufferSize /= static_cast<GLint>(sizeof(glm::mat4));
	m_maxNumObjects = std::min(static_cast<unsigned int>(maxBufferSize), m_maxNumObjects);

	initRenderTypes();
	initFBO();
}

/**************************************************************************************************/

void Manager::initRenderTypes() {
	/*
	 *	QUAD
	 */
	const std::vector<GLubyte> quadIdx = {
		3, 2, 0,
		0, 1, 3
	};
	auto renderType = Drawable::RenderTypeName::QUAD;
#ifdef LEGACY_MODE
	gl::Shader quadVert(GL_VERTEX_SHADER);
	quadVert.addSourceFromString("#version 330 core\n");
	quadVert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(m_maxNumObjects) + ";\n");
	quadVert.addSourceFromFile("shader/geometries/quad_legacy.vert");
	if (!quadVert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	// gl::Shader frag("shader/test/color_legacy.frag");
	gl::Shader frag("shader/lighting/direct_lighting_legacy.frag");
	m_renderTypes[renderType].prog.attachShader(quadVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.bind(GL_ARRAY_BUFFER);
	m_renderTypes[renderType].ibo.createMutableStorage(static_cast<unsigned int>(quadIdx.size() * sizeof(GLubyte)),
			GL_STATIC_DRAW, quadIdx.data());
	m_renderTypes[renderType].ibo.unbind();
#else
	gl::Shader quadVert("shader/geometries/quad.vert", "quad_instance_vert");
	// gl::Shader frag("shader/test/color.frag", "color_frag");
	gl::Shader frag("shader/lighting/direct_lighting.frag");
	m_renderTypes[renderType].prog.attachShader(quadVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(static_cast<unsigned int>(quadIdx.size() * sizeof(GLubyte)),
			0, quadIdx.data());
#endif
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0, size);
	};

	/*
	 *	CUBE
	 */
	const std::vector<GLushort> cubeIdx = {
		19, 18, 16,
		16, 17, 19,

		7, 3, 1,
		1, 5, 7,

		22, 23, 21,
		21, 20, 22,

		2, 6, 4,
		4, 0, 2,

		9, 8, 12,
		12, 13, 9,

		14, 15, 11,
		11, 10, 14
	};
	renderType = Drawable::RenderTypeName::CUBE;
#ifdef LEGACY_MODE
	gl::Shader cubeVert(GL_VERTEX_SHADER);
	cubeVert.addSourceFromString("#version 330 core\n");
	cubeVert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(m_maxNumObjects) + ";\n");
	cubeVert.addSourceFromFile("shader/geometries/cube_legacy.vert");
	if (!cubeVert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	m_renderTypes[renderType].prog.attachShader(cubeVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.bind(GL_ARRAY_BUFFER);
	m_renderTypes[renderType].ibo.createMutableStorage(
			static_cast<unsigned int>(cubeIdx.size() * sizeof(GLushort)),
			GL_STATIC_DRAW,	cubeIdx.data());
	m_renderTypes[renderType].ibo.unbind();
#else
	gl::Shader cubeVert("shader/geometries/cube.vert", "cube_instance_vert");
	m_renderTypes[renderType].prog.attachShader(cubeVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(
			static_cast<unsigned int>(cubeIdx.size() * sizeof(GLushort)),
			0, cubeIdx.data());
#endif
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, size);
	};
}

/**************************************************************************************************/

void Manager::initFBO() {
#ifdef LEGACY_MODE
	m_depthTex.bind();
	m_depthTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_DEPTH_COMPONENT32F);
	m_normalTex.bind();
	m_normalTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGB32F);
	m_colorTex.bind();
	m_colorTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGBA32F);
	m_positionTex.bind();
	m_positionTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGB32F);
	m_lightingTex.bind();
	m_lightingTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGBA32F);

	m_fbo.bind();
	m_fbo.attachTexture(GL_DEPTH_ATTACHMENT, m_depthTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT0, m_normalTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT1, m_colorTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT2, m_positionTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT3, m_lightingTex, 0);
	if (!m_fbo.isComplete()) {
		LOG_ERROR("Incomplete FBO!");
	}
	m_fbo.unbind();
#else
	m_depthTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_DEPTH_COMPONENT32F);
	m_normalTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGB32F);
	m_colorTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGBA32F);
	m_positionTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGB32F);
	m_lightingTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGBA32F);

	m_fbo.attachTexture(GL_DEPTH_ATTACHMENT, m_depthTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT0, m_normalTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT1, m_colorTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT2, m_positionTex, 0);
	m_fbo.attachTexture(GL_COLOR_ATTACHMENT3, m_lightingTex, 0);
	if (!m_fbo.isComplete(GL_FRAMEBUFFER)) {
		LOG_ERROR("Incomplete FBO!");
	}
#endif
}

/**************************************************************************************************/

void Manager::draw() {

	m_fbo.bind();
	m_fbo.draw({GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3});

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	for (const auto & drawablePair : m_drawables) {
		const auto & drawType = drawablePair.second;
		if (drawType.objects.size() == 0) {
			continue;
		}
		const auto renderType = drawType.objects[0].lock()->getRenderType();
		auto & prog = m_renderTypes[renderType].prog;
		prog.use();

#ifdef LEGACY_MODE
		const auto index = glGetUniformBlockIndex(static_cast<GLuint>(prog), "ModelMatrixBuffer");
		glUniformBlockBinding(static_cast<GLuint>(prog), index, k_modelBufferBinding);
		const auto bufferEnum = GL_UNIFORM_BUFFER;
#else
		const auto bufferEnum = GL_SHADER_STORAGE_BUFFER;
#endif

		prog["ViewProj"] = m_cam.getProjMatrix() * m_cam.getViewMatrix();
		prog["col"] = drawType.col;
		glBindBufferBase(bufferEnum, k_modelBufferBinding, drawType.modelBuffer);
		drawType.vao.bind();
		m_renderTypes[renderType].drawCall(static_cast<GLsizei>(drawType.objects.size()));
	}

	m_fbo.unbind();

#ifdef LEGACY_MODE
	m_fbo.bind(GL_READ_FRAMEBUFFER);
	glDrawBuffer(GL_BACK);
#endif
	m_fbo.blitAttachment(GL_COLOR_ATTACHMENT0,
			{0, 0, m_screenSize.x / 2, m_screenSize.y / 2});
	m_fbo.blitAttachment(GL_COLOR_ATTACHMENT1,
			{m_screenSize.x / 2, 0, m_screenSize.x, m_screenSize.y / 2});
	m_fbo.blitAttachment(GL_COLOR_ATTACHMENT2,
			{0, m_screenSize.y / 2, m_screenSize.x / 2, m_screenSize.y});
	m_fbo.blitAttachment(GL_COLOR_ATTACHMENT3,
			{m_screenSize.x / 2, m_screenSize.y / 2, m_screenSize.x, m_screenSize.y});
#ifdef LEGACY_MODE
	m_fbo.unbind();
#endif

}

/**************************************************************************************************/

void Manager::add(const std::shared_ptr<Drawable> & drawable) {
	const auto type = drawable->getType();
	const auto renderType = drawable->getRenderType();
	const auto typeSize = static_cast<unsigned int>(sizeof(glm::mat4));
#ifdef LEGACY_MODE
	if (m_drawables.count(type) == 0) {
		// color
		m_drawables[type].col = drawable->getColor();

		// vao
		m_drawables[type].vao.bind();
		m_renderTypes[renderType].ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
		m_drawables[type].vao.unbind();
		m_renderTypes[renderType].ibo.unbind();

		// buffer
		m_drawables[type].modelBuffer.bind(GL_UNIFORM_BUFFER);
		m_drawables[type].modelBuffer.createMutableStorage(m_maxNumObjects * typeSize,
				GL_DYNAMIC_DRAW);
		m_drawables[type].modelBuffer.unbind();
	}

	const auto offset = static_cast<unsigned int>(m_drawables[type].objects.size()) * typeSize;
	m_drawables[type].objects.emplace_back(drawable);
	m_drawables[type].modelBuffer.bind(GL_UNIFORM_BUFFER);
	m_drawables[type].modelBuffer.setData(offset, typeSize, glm::value_ptr(drawable->getModelMatrix()));
	m_drawables[type].modelBuffer.unbind();
#else
	if (m_drawables.count(type) == 0) {
		// color
		m_drawables[type].col = drawable->getColor();
		// vao
		m_drawables[type].vao.bindElementBuffer(m_renderTypes[renderType].ibo);
		// buffer
		m_drawables[type].modelBuffer.createImmutableStorage(m_maxNumObjects * typeSize,
				GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
	}

	const auto offset = static_cast<unsigned int>(m_drawables[type].objects.size()) * typeSize;
	m_drawables[type].objects.emplace_back(drawable);
	m_drawables[type].modelBuffer.setData(offset, typeSize, glm::value_ptr(drawable->getModelMatrix()));
#endif
}

/**************************************************************************************************/

void Manager::setScreenSize(const glm::uvec2 & size) {
	m_screenSize = size;
}

/**************************************************************************************************/
