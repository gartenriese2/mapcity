#pragma once

#include <MonoEngine/gui.hpp>

class Gui {

	public:

		Gui(std::unique_ptr<engine::Gui> &);

		void render();

		void setWorldPosition(const glm::vec3 &);

	private:

		std::unique_ptr<engine::Gui> & m_engineGuiPtr;

		glm::vec3 m_wPos;

};
