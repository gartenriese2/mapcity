#pragma once

#include "drawable.hpp"

#include <MonoEngine/gl/program.hpp>
#include <MonoEngine/gl/buffer.hpp>
#include <MonoEngine/gl/vertexarray.hpp>

#include <vector>
#include <memory>
#include <map>

namespace core {
	class Camera;
}

class Manager {

	public:

		Manager(core::Camera &);

		void draw();
		void add(const std::shared_ptr<Drawable> &);

	private:

		void initRenderTypes();

		core::Camera & m_cam;

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
