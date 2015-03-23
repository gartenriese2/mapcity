#pragma once

#include "manager.hpp"
#include "input.hpp"
#include "gui.hpp"

#include <MonoEngine/engine.hpp>
#include <MonoEngine/core/camera.hpp>

class Rendering {

	public:

		Rendering(const glm::uvec2 &);

		Manager & getManager();
		std::unique_ptr<core::Input> & getInputPtr();

		bool render();

	private:

		void init(const glm::uvec2 &);

		engine::Engine m_engine;
		core::Camera m_cam;

		Manager m_manager;
		Input m_input;
		Gui m_gui;

};
