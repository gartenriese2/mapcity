#include "rendering.hpp"

#include "conversion.hpp"

#include <MonoEngine/core/log.hpp>
#include <MonoEngine/extern/imgui.h>

Rendering::Rendering(const glm::uvec2 & size)
  : m_engine{size, "MapCity", true},
	m_manager{m_cam, size}
{
	init(size);
}

void Rendering::init(const glm::uvec2 & size) {
	m_engine.showFPS(true);
	m_engine.getInputPtr()->addKeyFunc([&](const int key, const int, const int action, const int){
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(m_engine.getWindowPtr()->getGLFWWindow(), GL_TRUE);
		}
	});

	m_engine.getInputPtr()->addMouseCursorFunc([&](const double x, const double y){
		m_mousePos = {static_cast<unsigned int>(x), static_cast<unsigned int>(y)};
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

Manager & Rendering::getManager() {
	return m_manager;
}

bool Rendering::render() {
	m_manager.draw();

	const auto wPos = graphicsToGame(m_manager.getWorldPos(m_mousePos.x, m_mousePos.y));

	m_engine.getGuiPtr()->newFrame();
	ImGui::Begin("Main Menu");
	ImGui::Text("wPos: (%.2f|%.2f|%.2f)", wPos.x, wPos.y, wPos.z);
	ImGui::End();

	return m_engine.render();
}
