#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdio.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Render.hpp"

using namespace glm;
using namespace std;

class Window {
public:
	Window();
	~Window();
	int createWindow(int, int);
	void loop();
private:
	Render render;
	GLuint LoadShaders(const char *,const char *);
};

#endif
