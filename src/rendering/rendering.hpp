#pragma once

#include "manager.hpp"

#include <MonoEngine/engine.hpp>
#include <MonoEngine/core/camera.hpp>

class Rendering {

	public:

		Rendering(const glm::uvec2 &);

		Manager & getManager();

		bool render();

	private:

		void init(const glm::uvec2 &);

		engine::Engine m_engine;
		core::Camera m_cam;

		Manager m_manager;

};
