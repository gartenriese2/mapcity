#include "drawablemanager.hpp"

#include <MonoEngine/core/camera.hpp>
#include <MonoEngine/core/log.hpp>
#include <MonoEngine/gl/shader.hpp>

/**************************************************************************************************/

constexpr auto k_modelBufferBinding = 0u;
constexpr auto k_colorBufferBinding = 1u;
constexpr auto k_miscBufferBinding = 2u;
constexpr auto k_modelTypeSize = static_cast<unsigned int>(sizeof(glm::mat4));
constexpr auto k_colorTypeSize = static_cast<unsigned int>(sizeof(glm::vec4));
constexpr auto k_miscTypeSize = static_cast<unsigned int>(sizeof(glm::vec4));
constexpr auto k_maxNumObjects = 1000u;

/**************************************************************************************************/

DrawableManager::DrawableManager(core::Camera & cam, const glm::uvec2 & size)
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

void DrawableManager::initRenderTypes() {

	/*
	 *	precalls
	 */
	auto multicolorPreCall = [](gl::Program & prog, const DrawableType & drawType, const core::Camera & cam){
		prog.use();
#ifdef LEGACY_MODE
		const auto modelIndex = glGetUniformBlockIndex(static_cast<GLuint>(prog), "ModelMatrixBuffer");
		glUniformBlockBinding(static_cast<GLuint>(prog), modelIndex, k_modelBufferBinding);
		glBindBufferBase(GL_UNIFORM_BUFFER, k_modelBufferBinding, drawType.modelBuffer);
		const auto colorIndex = glGetUniformBlockIndex(static_cast<GLuint>(prog), "ColorBuffer");
		glUniformBlockBinding(static_cast<GLuint>(prog), colorIndex, k_colorBufferBinding);
		glBindBufferBase(GL_UNIFORM_BUFFER, k_colorBufferBinding, drawType.colorBuffer);
#else
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, k_modelBufferBinding, drawType.modelBuffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, k_colorBufferBinding, drawType.colorBuffer);
#endif

		prog["ViewProj"] = cam.getProjMatrix() * cam.getViewMatrix();
		prog["View"] = cam.getViewMatrix();
		prog["lightDir"] = glm::vec3(1.f, 2.f, -3.f);

		drawType.vao.bind();
	};
	auto fanPreCall = [](gl::Program & prog, const DrawableType & drawType, const core::Camera & cam){
		prog.use();
#ifdef LEGACY_MODE
		const auto modelIndex = glGetUniformBlockIndex(static_cast<GLuint>(prog), "ModelMatrixBuffer");
		glUniformBlockBinding(static_cast<GLuint>(prog), modelIndex, k_modelBufferBinding);
		glBindBufferBase(GL_UNIFORM_BUFFER, k_modelBufferBinding, drawType.modelBuffer);
		const auto colorIndex = glGetUniformBlockIndex(static_cast<GLuint>(prog), "ColorBuffer");
		glUniformBlockBinding(static_cast<GLuint>(prog), colorIndex, k_colorBufferBinding);
		glBindBufferBase(GL_UNIFORM_BUFFER, k_colorBufferBinding, drawType.colorBuffer);
		const auto miscIndex = glGetUniformBlockIndex(static_cast<GLuint>(prog), "MiscBuffer");
		glUniformBlockBinding(static_cast<GLuint>(prog), miscIndex, k_miscBufferBinding);
		glBindBufferBase(GL_UNIFORM_BUFFER, k_miscBufferBinding, drawType.miscBuffer);
#else
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, k_modelBufferBinding, drawType.modelBuffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, k_colorBufferBinding, drawType.colorBuffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, k_miscBufferBinding, drawType.miscBuffer);
#endif

		prog["ViewProj"] = cam.getProjMatrix() * cam.getViewMatrix();
		prog["View"] = cam.getViewMatrix();
		prog["lightDir"] = glm::vec3(1.f, 2.f, -3.f);

		drawType.vao.bind();
	};
	auto unicolorPreCall = [](gl::Program & prog, const DrawableType & drawType, const core::Camera & cam){
		prog.use();
#ifdef LEGACY_MODE
		const auto modelIndex = glGetUniformBlockIndex(static_cast<GLuint>(prog), "ModelMatrixBuffer");
		glUniformBlockBinding(static_cast<GLuint>(prog), modelIndex, k_modelBufferBinding);
		glBindBufferBase(GL_UNIFORM_BUFFER, k_modelBufferBinding, drawType.modelBuffer);
#else
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, k_modelBufferBinding, drawType.modelBuffer);
#endif
		prog["col"] = drawType.col;
		prog["ViewProj"] = cam.getProjMatrix() * cam.getViewMatrix();
		prog["View"] = cam.getViewMatrix();
		prog["lightDir"] = glm::vec3(1.f, 2.f, -3.f);

		drawType.vao.bind();
	};

	/*
	 *	UNICOLORED QUAD
	 */
	const std::vector<GLubyte> quadIdx = {
		3, 2, 0,
		0, 1, 3
	};
	auto renderType = RenderTypeName::QUAD;
#ifdef LEGACY_MODE
	gl::Shader quadVert(GL_VERTEX_SHADER);
	quadVert.addSourceFromString("#version 330 core\n");
	quadVert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(m_maxNumObjects) + ";\n");
	quadVert.addSourceFromFile("shader/geometries/quad_legacy.vert");
	if (!quadVert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	gl::Shader frag("shader/lighting/direct_lighting_legacy.frag");
	m_renderTypes[renderType].prog.attachShader(quadVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.bind(GL_ARRAY_BUFFER);
	m_renderTypes[renderType].ibo.createMutableStorage(static_cast<unsigned int>(quadIdx.size() * sizeof(GLubyte)),
			GL_STATIC_DRAW, quadIdx.data());
	m_renderTypes[renderType].ibo.unbind();
#else
	gl::Shader quadVert("shader/geometries/quad.vert", "quad_instance_vert");
	gl::Shader frag("shader/lighting/direct_lighting.frag");
	m_renderTypes[renderType].prog.attachShader(quadVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(static_cast<unsigned int>(quadIdx.size() * sizeof(GLubyte)),
			0, quadIdx.data());
#endif
	// drawCall
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0, size);
	};
	// preCall
	m_renderTypes[renderType].preCall = unicolorPreCall;

	/*
	 *	MULTICOLORED QUAD
	 */
	renderType = RenderTypeName::MULTICOLOR_QUAD;
#ifdef LEGACY_MODE
	gl::Shader multicolorQuadVert(GL_VERTEX_SHADER);
	multicolorQuadVert.addSourceFromString("#version 330 core\n");
	multicolorQuadVert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(m_maxNumObjects) + ";\n");
	multicolorQuadVert.addSourceFromFile("shader/geometries/multicolor_quad_legacy.vert");
	if (!multicolorQuadVert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	m_renderTypes[renderType].prog.attachShader(multicolorQuadVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.bind(GL_ARRAY_BUFFER);
	m_renderTypes[renderType].ibo.createMutableStorage(
			static_cast<unsigned int>(quadIdx.size() * sizeof(GLubyte)),
			GL_STATIC_DRAW,	quadIdx.data());
	m_renderTypes[renderType].ibo.unbind();
#else
	gl::Shader multicolorQuadVert("shader/geometries/multicolor_quad.vert", "multicolor_quad_vert");
	m_renderTypes[renderType].prog.attachShader(multicolorQuadVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(static_cast<unsigned int>(quadIdx.size() * sizeof(GLubyte)),
			0, quadIdx.data());
#endif
	// drawCall
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0, size);
	};
	// preCall
	m_renderTypes[renderType].preCall = multicolorPreCall;

	/*
	 *	UNICOLORED CUBE
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
	renderType = RenderTypeName::CUBE;
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
	gl::Shader cubeVert("shader/geometries/cube.vert", "cube_vert");
	m_renderTypes[renderType].prog.attachShader(cubeVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(static_cast<unsigned int>(cubeIdx.size() * sizeof(GLushort)),
			0, cubeIdx.data());
#endif
	// drawCall
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, size);
	};
	// preCall
	m_renderTypes[renderType].preCall = unicolorPreCall;

	/*
	 *	MULTICOLORED CUBE
	 */
	renderType = RenderTypeName::MULTICOLOR_CUBE;
#ifdef LEGACY_MODE
	gl::Shader multicolorCubeVert(GL_VERTEX_SHADER);
	multicolorCubeVert.addSourceFromString("#version 330 core\n");
	multicolorCubeVert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(m_maxNumObjects) + ";\n");
	multicolorCubeVert.addSourceFromFile("shader/geometries/multicolor_cube_legacy.vert");
	if (!multicolorCubeVert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	m_renderTypes[renderType].prog.attachShader(multicolorCubeVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.bind(GL_ARRAY_BUFFER);
	m_renderTypes[renderType].ibo.createMutableStorage(
			static_cast<unsigned int>(cubeIdx.size() * sizeof(GLushort)),
			GL_STATIC_DRAW,	cubeIdx.data());
	m_renderTypes[renderType].ibo.unbind();
#else
	gl::Shader multicolorCubeVert("shader/geometries/multicolor_cube.vert", "multicolor_cube_vert");
	m_renderTypes[renderType].prog.attachShader(multicolorCubeVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(static_cast<unsigned int>(cubeIdx.size() * sizeof(GLushort)),
			0, cubeIdx.data());
#endif
	// drawCall
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0, size);
	};
	// preCall
	m_renderTypes[renderType].preCall = multicolorPreCall;

	/*
	 *	FAN
	 */
	std::vector<GLushort> fanIdx;
	constexpr auto segments = 100u;
	fanIdx.reserve(segments + 2);
	for (auto i = 0u; i < segments + 2; ++i) {
		fanIdx.emplace_back(i);
	}
	renderType = RenderTypeName::FAN;
#ifdef LEGACY_MODE
	gl::Shader fanVert(GL_VERTEX_SHADER);
	fanVert.addSourceFromString("#version 330 core\n");
	fanVert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(m_maxNumObjects) + ";\n");
	fanVert.addSourceFromFile("shader/geometries/fan_legacy.vert");
	if (!fanVert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	m_renderTypes[renderType].prog.attachShader(fanVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.bind(GL_ARRAY_BUFFER);
	m_renderTypes[renderType].ibo.createMutableStorage(
			static_cast<unsigned int>(fanIdx.size() * sizeof(GLushort)),
			GL_STATIC_DRAW,	fanIdx.data());
	m_renderTypes[renderType].ibo.unbind();
#else
	gl::Shader fanVert("shader/geometries/fan.vert", "fan_vert");
	m_renderTypes[renderType].prog.attachShader(fanVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(static_cast<unsigned int>(fanIdx.size() * sizeof(GLushort)),
			0, fanIdx.data());
#endif
	// drawCall
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLE_FAN, segments + 2, GL_UNSIGNED_SHORT, 0, size);
	};
	// preCall
	m_renderTypes[renderType].preCall = fanPreCall;

	/*
	 *	ANNULUS
	 */
	std::vector<GLushort> annulusIdx;
	annulusIdx.reserve(2 * segments + 2);
	for (auto i = 0u; i < 2 * segments + 2; ++i) {
		annulusIdx.emplace_back(i);
	}
	renderType = RenderTypeName::ANNULUS;
#ifdef LEGACY_MODE
	gl::Shader annulusVert(GL_VERTEX_SHADER);
	annulusVert.addSourceFromString("#version 330 core\n");
	annulusVert.addSourceFromString("const int NUM_MATRICES = " + std::to_string(m_maxNumObjects) + ";\n");
	annulusVert.addSourceFromFile("shader/geometries/circlesegment_legacy.vert");
	if (!annulusVert.compileSource()) {
		LOG_ERROR("could not compile vertex shader!");
	}
	m_renderTypes[renderType].prog.attachShader(annulusVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.bind(GL_ARRAY_BUFFER);
	m_renderTypes[renderType].ibo.createMutableStorage(
			static_cast<unsigned int>(annulusIdx.size() * sizeof(GLushort)),
			GL_STATIC_DRAW,	annulusIdx.data());
	m_renderTypes[renderType].ibo.unbind();
#else
	gl::Shader annulusVert("shader/geometries/circlesegment.vert", "circlesegment_vert");
	m_renderTypes[renderType].prog.attachShader(annulusVert);
	m_renderTypes[renderType].prog.attachShader(frag);

	m_renderTypes[renderType].ibo.createImmutableStorage(static_cast<unsigned int>(annulusIdx.size() * sizeof(GLushort)),
			0, annulusIdx.data());
#endif
	// drawCall
	m_renderTypes[renderType].drawCall = [](const GLsizei size){
		glDrawElementsInstanced(GL_TRIANGLE_STRIP, 2 * segments + 2, GL_UNSIGNED_SHORT, 0, size);
	};
	// preCall
	m_renderTypes[renderType].preCall = fanPreCall;
}

/**************************************************************************************************/

void DrawableManager::initFBO() {
#ifdef LEGACY_MODE
	m_depthTex.bind();
	m_depthTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_DEPTH_COMPONENT32F);
	m_normalTex.bind();
	m_normalTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGBA32F);
	m_colorTex.bind();
	m_colorTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGBA32F);
	m_positionTex.bind();
	m_positionTex.createImmutableStorage(m_screenSize.x, m_screenSize.y, GL_RGBA32F);
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

void DrawableManager::draw() {
	m_fbo.bind();
	m_fbo.draw({GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3});

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	for (const auto & drawablePair : m_drawables) {
		const auto & drawType = drawablePair.second;
		if (drawType.objects.size() == 0 || !drawType.visible) {
			continue;
		}
		if (drawType.dynamic) {
			updateBuffer(drawablePair.first);
		}
		const auto renderType = drawType.objects[0].lock()->renderType;
		m_renderTypes[renderType].preCall(m_renderTypes[renderType].prog, drawType, m_cam);
		m_renderTypes[renderType].drawCall(static_cast<GLsizei>(drawType.objects.size()));
	}

	m_fbo.unbind();

#ifdef LEGACY_MODE
	m_fbo.bind(GL_READ_FRAMEBUFFER);
	glDrawBuffer(GL_BACK);
#endif
	m_fbo.blitAttachment(GL_COLOR_ATTACHMENT3, {0, 0, m_screenSize.x, m_screenSize.y});
#ifdef LEGACY_MODE
	m_fbo.unbind();
#endif

}

/**************************************************************************************************/

void DrawableManager::add(const std::shared_ptr<Drawable> & drawable) {
	const auto type = drawable->type;
	const auto renderType = drawable->renderType;

	const auto unicolored = drawable->unicolored;

	if (m_drawables.count(type) == 0) {
		// color
		m_drawables[type].unicolored = unicolored;
		if (unicolored) {
			m_drawables[type].col = drawable->color;
		}
		// dynamic
		m_drawables[type].dynamic = drawable->dynamic;
		// visible
		m_drawables[type].visible = true;
#ifdef LEGACY_MODE
		// vao
		m_drawables[type].vao.bind();
		m_renderTypes[renderType].ibo.bind(GL_ELEMENT_ARRAY_BUFFER);
		m_drawables[type].vao.unbind();
		m_renderTypes[renderType].ibo.unbind();

		// buffer
		m_drawables[type].modelBuffer.bind(GL_UNIFORM_BUFFER);
		m_drawables[type].modelBuffer.createMutableStorage(m_maxNumObjects * k_modelTypeSize,
				GL_DYNAMIC_DRAW);
		m_drawables[type].modelBuffer.unbind();
		if (!unicolored) {
			m_drawables[type].colorBuffer.bind(GL_UNIFORM_BUFFER);
			m_drawables[type].colorBuffer.createMutableStorage(m_maxNumObjects * k_colorTypeSize,
					GL_DYNAMIC_DRAW);
			m_drawables[type].colorBuffer.unbind();
		}
		m_drawables[type].miscBuffer.bind(GL_UNIFORM_BUFFER);
		m_drawables[type].miscBuffer.createMutableStorage(m_maxNumObjects * k_miscTypeSize,
				GL_DYNAMIC_DRAW);
		m_drawables[type].miscBuffer.unbind();

#else
		// vao
		m_drawables[type].vao.bindElementBuffer(m_renderTypes[renderType].ibo);
		// buffer
		m_drawables[type].modelBuffer.createImmutableStorage(m_maxNumObjects * k_modelTypeSize,
				GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
		if (!unicolored) {
			m_drawables[type].colorBuffer.createImmutableStorage(m_maxNumObjects * k_colorTypeSize,
					GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
		}
		m_drawables[type].miscBuffer.createImmutableStorage(m_maxNumObjects * k_miscTypeSize,
				GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
#endif
	}

	if (static_cast<unsigned int>(m_drawables[type].objects.size()) >= m_maxNumObjects) {
		updateBuffer(type);
	}
	if (static_cast<unsigned int>(m_drawables[type].objects.size()) >= m_maxNumObjects) {
		// still full!
		LOG_WARNING(type + " Buffer is full! Not adding any more objects!");
		return;
	}

	const auto modelOffset = static_cast<unsigned int>(m_drawables[type].objects.size()) * k_modelTypeSize;
	const auto colorOffset = static_cast<unsigned int>(m_drawables[type].objects.size()) * k_colorTypeSize;
	const auto miscOffset = static_cast<unsigned int>(m_drawables[type].objects.size()) * k_miscTypeSize;
	m_drawables[type].objects.emplace_back(drawable);
#ifdef LEGACY_MODE
	m_drawables[type].modelBuffer.bind(GL_UNIFORM_BUFFER);
	m_drawables[type].modelBuffer.setData(modelOffset, k_modelTypeSize, glm::value_ptr(drawable->getModelMatrix()));
	m_drawables[type].modelBuffer.unbind();
	if (!unicolored) {
		m_drawables[type].colorBuffer.bind(GL_UNIFORM_BUFFER);
		m_drawables[type].colorBuffer.setData(colorOffset, k_colorTypeSize, glm::value_ptr(drawable->color));
		m_drawables[type].colorBuffer.unbind();
	}
	m_drawables[type].miscBuffer.bind(GL_UNIFORM_BUFFER);
	m_drawables[type].miscBuffer.setData(miscOffset, k_miscTypeSize, glm::value_ptr(drawable->misc));
	m_drawables[type].miscBuffer.unbind();
#else
	m_drawables[type].modelBuffer.setData(modelOffset, k_modelTypeSize, glm::value_ptr(drawable->getModelMatrix()));
	if (!unicolored) {
		m_drawables[type].colorBuffer.setData(colorOffset, k_colorTypeSize, glm::value_ptr(drawable->color));
	}
	m_drawables[type].miscBuffer.setData(miscOffset, k_miscTypeSize, glm::value_ptr(drawable->misc));
#endif
}

/**************************************************************************************************/

void DrawableManager::setScreenSize(const glm::uvec2 & size) {
	m_screenSize = size;
}

/**************************************************************************************************/

glm::vec3 DrawableManager::getWorldPos(const glm::uvec2 & pos) const {
	glm::vec3 wPos;
	m_fbo.bind(GL_READ_FRAMEBUFFER);
	m_fbo.read(GL_COLOR_ATTACHMENT2);
	const auto size = m_fbo.getAttachmentSize(GL_COLOR_ATTACHMENT2);
	glReadPixels(static_cast<GLint>(pos.x), size.y - static_cast<GLint>(pos.y), 1, 1, GL_RGB,
			GL_FLOAT, &wPos);
	m_fbo.unbind();
	return wPos;
}

/**************************************************************************************************/

void DrawableManager::updateBuffer(const std::string & type) {
	auto & objects = m_drawables[type].objects;

	std::vector<glm::mat4> modelVec;
	std::vector<glm::vec4> colorVec;
	std::vector<glm::vec4> miscVec;
	modelVec.reserve(objects.size());
	colorVec.reserve(objects.size());
	miscVec.reserve(objects.size());

	auto it = objects.begin();
	while (it != objects.end()) {
		if (it->expired()) {
			it = objects.erase(it);
			continue;
		}
		modelVec.emplace_back(it->lock()->getModelMatrix());
		colorVec.emplace_back(it->lock()->color);
		miscVec.emplace_back(it->lock()->misc);
		++it;
	}

#ifdef LEGACY_MODE
	m_drawables[type].modelBuffer.bind(GL_UNIFORM_BUFFER);
	m_drawables[type].modelBuffer.setData(
			0,
			k_modelTypeSize * static_cast<unsigned int>(modelVec.size()),
			modelVec.data());
	m_drawables[type].modelBuffer.unbind();
	if (!m_drawables[type].unicolored) {
		m_drawables[type].colorBuffer.bind(GL_UNIFORM_BUFFER);
		m_drawables[type].colorBuffer.setData(
				0,
				k_colorTypeSize * static_cast<unsigned int>(colorVec.size()),
				colorVec.data());
		m_drawables[type].colorBuffer.unbind();
	}
	m_drawables[type].miscBuffer.bind(GL_UNIFORM_BUFFER);
	m_drawables[type].miscBuffer.setData(
			0,
			k_miscTypeSize * static_cast<unsigned int>(miscVec.size()),
			miscVec.data());
	m_drawables[type].miscBuffer.unbind();
#else
	m_drawables[type].modelBuffer.setData(
			0,
			k_modelTypeSize * static_cast<unsigned int>(modelVec.size()),
			modelVec.data());
	if (!m_drawables[type].unicolored) {
		m_drawables[type].colorBuffer.setData(
				0,
				k_colorTypeSize * static_cast<unsigned int>(colorVec.size()),
				colorVec.data());
	}
	m_drawables[type].miscBuffer.setData(
			0,
			k_miscTypeSize * static_cast<unsigned int>(miscVec.size()),
			miscVec.data());
#endif
}

/**************************************************************************************************/

void DrawableManager::hide(const std::string & type) {
	if (m_drawables.count(type) == 0) {
		LOG_WARNING("Type " + type + " does not exist -> cannot hide it");
		return;
	}
	m_drawables[type].visible = false;
}

/**************************************************************************************************/

void DrawableManager::show(const std::string & type) {
	if (m_drawables.count(type) == 0) {
		LOG_WARNING("Type " + type + " does not exist -> cannot show it");
		return;
	}
	m_drawables[type].visible = true;
}

/**************************************************************************************************/
