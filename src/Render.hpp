#ifndef RENDER_HPP
#define RENDER_HPP

#include "ogl.h"
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
