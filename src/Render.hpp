#ifndef RENDER_HPP
#define RENDER_HPP

#include <GL/glew.h>
#include <GL/glfw.h>
#include <GL/gl.h>
#include <iostream>

class Render {
public:
	Render();
	~Render();
	void renderTriangle();
	void setTriangle();
private:
	// This will identify our vertex buffer
	GLuint vertexbuffer;
};

#endif
