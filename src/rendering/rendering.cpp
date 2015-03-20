#include "rendering.hpp"

Rendering::Rendering(const glm::uvec2 & size)
  : m_engine{size, "MapCity", true},
	m_manager{m_cam}
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

	m_cam.setRatio(static_cast<float>(size.x) / static_cast<float>(size.y));
	m_cam.setFov(glm::radians(45.f));
	m_cam.translate({0.f, 0.f, 500.f});
}

Manager & Rendering::getManager() {
	return m_manager;
}

bool Rendering::render() {
	m_manager.draw();
	return m_engine.render();
}
