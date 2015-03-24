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

namespace core {
	class Camera;
}

class Manager {

	public:

		Manager(core::Camera &, const glm::uvec2 &);

		void draw();
		void add(const std::shared_ptr<Drawable> &);
		void updateBuffer(const std::string &);

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

		struct RenderType {
			gl::Program prog;
			gl::Buffer ibo;
			std::function<void(GLsizei)> drawCall;
		};
		std::map<Drawable::RenderTypeName, RenderType> m_renderTypes;

		struct DrawableType {
			std::vector<std::weak_ptr<Drawable>> objects;
			glm::vec3 col;
			gl::VertexArray vao;
			gl::Buffer modelBuffer;
		};
		std::map<std::string, DrawableType> m_drawables;

		unsigned int m_maxNumObjects;

};
