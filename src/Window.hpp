#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdio.h>

#include "Shader.hpp"
#include "World.hpp"

using namespace glm;
using namespace std;

class Window {
public:
	Window(int, int);
	~Window();
	int init();
	int createWindow(int, int);
	void loop();
	void keyhandler();
	void mousehandler();

	inline World& getWorld() { return this->world; }
private:

	int m_width;
	int m_height;
	Shader shader;
	World world;
	GLuint simpleShader;
};

#endif