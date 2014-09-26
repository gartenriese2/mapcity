#include "engine.hpp"

#include "window.hpp"
#include "debug.hpp"
#include "objects/objectinterface.hpp"

Engine::Engine() {

	init();

}

Engine::~Engine() {

	for (auto & thread : m_windowThreads) {
		thread.second.reset(nullptr);
	}

	glfwTerminate();

}

void Engine::init() {

	if (!glfwInit()) {
		Debug::log("Could not initialize GLFW!");
		exit(0);
	}

}

/**
 * @brief Creates a new thread and opens a window in windowed mode.
 * @details [long description]
 * 
 * @param width The width of the window
 * @param height The height of the window
 * @param title The title of the window
 * @return A WindowID, which is used to control the window
 */
const WindowID Engine::createWindow(unsigned int width, unsigned int height, const std::string & title) {

	std::shared_ptr<Window> ptr(new Window(width, height, title, false));

	WindowID id(ptr);

	m_windowThreads[id()] = std::unique_ptr<WindowThread>(new WindowThread(ptr));

	while(!ptr->isInitialized());

	return id;

}

/**
 * @brief Creates a new thread and opens a window in fullscreen mode.
 * @details [long description]
 * 
 * @param width Number of pixels in horizontal direction.
 * @param int [description]
 * @param title [description]
 * @return A WindowID, which is used to control the window
 */
const WindowID Engine::createFullscreenWindow(unsigned int width, unsigned int height, const std::string & title) {

	std::shared_ptr<Window> ptr(new Window(width, height, title, true));

	WindowID id(ptr);

	m_windowThreads[id()] = std::unique_ptr<WindowThread>(new WindowThread(ptr));

	while(!ptr->isInitialized());

	return id;

}
