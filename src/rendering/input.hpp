#pragma once

#include <MonoEngine/core/input.hpp>
#include <glm/glm.hpp>

#include <memory>

class Input {

	public:

		Input(std::unique_ptr<core::Input> &);

		const glm::uvec2 & getMousePos() const;

		bool hasLeftClicked();

	private:

		std::unique_ptr<core::Input> & m_engineInputPtr;

		glm::uvec2 m_mousePos;
		bool m_leftMouseButtonDown;
		bool m_leftMouseButtonRelease;
		glm::uvec2 m_leftMouseButtonDownPos;
		glm::uvec2 m_leftMouseButtonReleasePos;
		double m_scrollOffset;

};
