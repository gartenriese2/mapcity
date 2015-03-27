#include "rendering.hpp"

#include "conversion.hpp"

#include <MonoEngine/core/log.hpp>

/**************************************************************************************************/

Rendering::Rendering(const glm::uvec2 & size)
  : m_engine{size, "MapCity", true},
	m_manager{m_cam, size},
	m_input{m_engine.getInputPtr()},
	m_gui{m_engine.getGuiPtr()}
{
	init(size);
}

/**************************************************************************************************/

void Rendering::init(const glm::uvec2 & size) {
	m_engine.showFPS(true);
	m_engine.getInputPtr()->addKeyFunc([&](const int key, const int, const int action, const int){
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(m_engine.getWindowPtr()->getGLFWWindow(), GL_TRUE);
		}
	});

	m_engine.getWindowPtr()->addWindowSizeFunc([&](const int width, const int height){
		m_manager.setScreenSize({width, height});
	});

	m_cam.setRatio(static_cast<float>(size.x) / static_cast<float>(size.y));
	m_cam.setFov(glm::radians(45.f));
	m_cam.translate(gameToGraphics(glm::vec3{0.f, -100.f, 500.f}));
	m_cam.pitch(glm::radians(10.f));

	glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
}

/**************************************************************************************************/

DrawableManager & Rendering::getDrawableManager() {
	return m_manager;
}

/**************************************************************************************************/

const std::unique_ptr<core::Input> & Rendering::getInputPtr() {
	return m_engine.getInputPtr();
}

/**************************************************************************************************/

bool Rendering::render() {
	if (m_gui.showPaths()) {
		m_manager.show("Path");
	} else {
		m_manager.hide("Path");
	}
	m_manager.draw();
	if (m_input.hasLeftClicked()) {
		m_gui.setWorldPosition(graphicsToGame(m_manager.getWorldPos(m_input.getMousePos())));
	}
	m_gui.render();
	return m_engine.render();
}

/**************************************************************************************************/
