#include "window.hpp"

#include "debug.hpp"

Window::Window(unsigned int width, unsigned int height, const std::string & title, bool fullscreen)
  : m_width(width),
	m_height(height),
	m_title(title),
	m_fullscreen(fullscreen),
	m_init(false)
{
}

Window::~Window() {
	
}

void Window::start() {

	m_window = glfwCreateWindow(static_cast<int>(m_width), static_cast<int>(m_height),
								m_title.c_str(), m_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		Debug::log("Could not create Window!");
		exit(0);
	}

	glfwMakeContextCurrent(m_window);
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		Debug::log("Cound not initialize GLEW!");
		Debug::log(glewGetErrorString(err));
		return;
	}

	if (glewIsSupported("GL_ARB_debug_output")) {
		
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		glDebugMessageCallback(&Window::debugCallback, stderr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, 0, GL_FALSE);
		
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		
	}

	glfwSetWindowUserPointer(m_window, this);

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow * window, int width, int height){
		
		const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		width = (width > mode->width) ? mode->width : width;
		height = (height > mode->height) ? mode->height : height;

		Window * win = static_cast<Window *>(glfwGetWindowUserPointer(window));
		win->setWidth(static_cast<unsigned int>(width));
		win->setHeight(static_cast<unsigned int>(height));

		Loop & loop = win->getLoop();
		loop.resizeRenderings(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
	
	});

	m_init = true;

	m_loop.start(m_window);
	glfwDestroyWindow(m_window);

}

void Window::debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
					 GLsizei length, const GLchar * message, const void * userParam) {

	const std::string output = formatDebugOutput(source, type, id, severity, message);
	Debug::log(output + "\n");

}

const std::string Window::formatDebugOutput(GLenum source, GLenum type,
	GLuint id, GLenum severity, const std::string & msg) {
	
	std::string sourceStr {"UNDEFINED"};
	switch (source) {
		case GL_DEBUG_SOURCE_API:
			sourceStr = "API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			sourceStr = "WINDOW_SYSTEM";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			sourceStr = "SHADER_COMPILER";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			sourceStr = "THIRD_PARTY";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			sourceStr = "APPLICATION";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			sourceStr = "OTHER";
			break;
	}

	std::string typeStr {"UNDEFINED"};
	switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			typeStr = "ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			typeStr = "DEPRECATED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			typeStr = "UNDEFINED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			typeStr = "PORTABILITY";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			typeStr = "PERFORMANCE";
			break;
		case GL_DEBUG_TYPE_MARKER:
			typeStr = "MARKER";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			typeStr = "PUSH_GROUP";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			typeStr = "POP_GROUP";
			break;
		case GL_DEBUG_TYPE_OTHER:
			typeStr = "OTHER";
			break;
	}

	std::string severityStr {"UNDEFINED"};
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			severityStr = "HIGH";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			severityStr = "MEDIUM";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			severityStr = "LOW";
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			severityStr = "NOTIFICATION";
			break;
	}

	return "OpenGL: " + msg + " [source=" + sourceStr + " type="
		+ typeStr + " severity=" + severityStr + " id=" + std::to_string(id) + "]";

}
