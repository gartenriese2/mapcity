#include "loop.hpp"

#include "program.hpp"
#include "../debug.hpp"
#include "../handler.hpp"

#include <mutex>

static std::mutex s_mutex;

Loop::Loop()
  : m_stop{false}
{

	m_mouseMoveEvent = [](double, double){};
	m_scrollEvent = [](double, double){};

}

void Loop::start(GLFWwindow * window) {

	glfwSetKeyCallback(window, [](GLFWwindow * windowPtr, int key, int scancode, int action, int mods){

		Window * win = static_cast<Window *>(glfwGetWindowUserPointer(windowPtr));
		Loop & loop = win->getLoop();

		if (loop.m_keyEvents.count(key) != 0 && (action == GLFW_PRESS || action == GLFW_REPEAT))
			loop.m_keyEvents.at(key)();

	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow * windowPtr, int button, int action, int mods){

		Window * win = static_cast<Window *>(glfwGetWindowUserPointer(windowPtr));
		Loop & loop = win->getLoop();

		if (loop.m_mouseClickEvents.count(button) != 0 && (action == GLFW_PRESS || action == GLFW_REPEAT))
			loop.m_mouseClickEvents.at(button)();

	});

	glfwSetCursorPosCallback(window, [](GLFWwindow * windowPtr, double xpos, double ypos){

		Window * win = static_cast<Window *>(glfwGetWindowUserPointer(windowPtr));
		Loop & loop = win->getLoop();

		loop.m_mouseMoveEvent(xpos, ypos);

	});

	glfwSetScrollCallback(window, [](GLFWwindow * windowPtr, double xoffset, double yoffset){

		Window * win = static_cast<Window *>(glfwGetWindowUserPointer(windowPtr));
		Loop & loop = win->getLoop();

		loop.m_scrollEvent(xoffset, yoffset);

	});

	while (!glfwWindowShouldClose(window) && !m_stop)
	{

		emptyCommands();

		render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

}

void Loop::render() {

	if (m_rendering) {
		m_rendering->draw();
	}

}

void Loop::addCommand(std::function<void()> func) {

	std::lock_guard<std::mutex> lock(s_mutex);

	m_commands.push(func);

}

void Loop::emptyCommands() {

	std::lock_guard<std::mutex> lock(s_mutex);

	while (!m_commands.empty()) {
		m_commands.front()();
		m_commands.pop();
	}

}

void Loop::addObjectsToRender(unsigned long renderID, std::set<unsigned long> objectIDs) {
	m_createdRenderings.at(renderID)->addObjects(objectIDs);
}

void Loop::removeObjectFromRender(unsigned long renderID, unsigned long objectID) {
	m_createdRenderings.at(renderID)->removeObject(objectID);
}

void Loop::resizeRenderings(unsigned int width, unsigned int height) {

	for (auto & r : m_createdRenderings) {
		r.second->changeBaseSize(width, height);
	}

}
