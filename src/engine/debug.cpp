#include "debug.hpp"

#include "gl/glincludes.hpp"

Debug * Debug::s_instance = nullptr;
std::mutex Debug::s_mutex;

Debug & Debug::instance() {

	static Cleanup cleanup;
	std::lock_guard<std::mutex> guard(s_mutex);
	if (s_instance == nullptr) {
		s_instance = new Debug();
	}

	return * s_instance;

}

Debug::Cleanup::~Cleanup() {
	
	std::lock_guard<std::mutex> gaurd(Debug::s_mutex);
	delete Debug::s_instance;
	Debug::s_instance = nullptr;

}

Debug::Debug() {
}

Debug::~Debug() {
}

void Debug::logGL() {

	GLenum e = glGetError();
	switch(e) {
		case GL_NO_ERROR:
			log("GL_NO_ERROR");
			break;
		case GL_INVALID_ENUM:
			log("GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			log("GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			log("GL_INVALID_OPERATION");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			log("GL_INVALID_FRAMEBUFFER_OPERATION");
			break;
		case GL_OUT_OF_MEMORY:
			log("GL_OUT_OF_MEMORY");
			break;
		default:
			log("NO STANDARD ERROR");
	}

}
