#pragma once

#include "drawable.hpp"

#include <MonoEngine/gl/program.hpp>
#include <MonoEngine/gl/buffer.hpp>
#include <MonoEngine/gl/vertexarray.hpp>
#include <MonoEngine/gl/texture.hpp>
#include <MonoEngine/gl/framebuffer.hpp>

#include <vector>
#include <memory>
#include <map>
#include <type_traits>

namespace core {
	class Camera;
}

class DrawableManager {

	public:

		DrawableManager(core::Camera &, const glm::uvec2 &);

		void draw();
		void add(const std::shared_ptr<Drawable> &);

		void updateBuffer(const std::string &);
		void hide(const std::string &);
		void show(const std::string &);

		void setScreenSize(const glm::uvec2 &);

		glm::vec3 getWorldPos(const glm::uvec2 &) const;

	private:

		void initRenderTypes();
		void initFBO();

		core::Camera & m_cam;
		glm::uvec2 m_screenSize;

		gl::Framebuffer m_fbo;
		gl::Texture m_depthTex;
		gl::Texture m_normalTex;
		gl::Texture m_colorTex;
		gl::Texture m_positionTex;
		gl::Texture m_lightingTex;

		struct DrawableType {
			bool visible;
			bool dynamic;
			bool unicolored;
			std::vector<std::weak_ptr<Drawable>> objects;
			glm::vec4 col;
			gl::VertexArray vao;
			gl::Buffer modelBuffer;
			gl::Buffer colorBuffer;
		};
		std::map<std::string, DrawableType> m_drawables;

		struct RenderType {
			gl::Program prog;
			gl::Buffer ibo;
			std::function<void(GLsizei)> drawCall;
			std::function<void(gl::Program &, const DrawableType &, const core::Camera &)> preCall;
		};
		std::map<RenderTypeName, RenderType> m_renderTypes;

		unsigned int m_maxNumObjects;

};
