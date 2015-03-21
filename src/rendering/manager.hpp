#pragma once

#include "drawable.hpp"

#include <MonoEngine/gl/program.hpp>
#include <MonoEngine/gl/buffer.hpp>
#include <MonoEngine/gl/vertexarray.hpp>

#include <vector>
#include <memory>

namespace core {
	class Camera;
}

class Manager {

	public:

		Manager(core::Camera &);

		void draw();

		void addStreet(const std::shared_ptr<Drawable> &);

	private:

		std::vector<std::weak_ptr<Drawable>> m_streets;

		core::Camera & m_cam;
		gl::Program m_prog;
		gl::Buffer m_ibo;
		gl::VertexArray m_vao;
		gl::Buffer m_modelMatrixBuffer;

#ifdef LEGACY_MODE
		unsigned int m_maxNumObjects;
#endif

};
