#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdio.h>
#include <time.h>

#include "Shader.hpp"
#include "World.hpp"
#include "Camera.hpp"

using namespace glm;
using namespace std;

class Window {
public:
	Window(int, int);
	~Window();
	void initCam(int, int);
	void loop();
	inline Camera * getCam() { return this->cam; }
	inline void setWorld(World * world) { this->world = world; }
private:

	int m_width;
	int m_height;

	int m_mousePosX, m_mousePosY, m_mouseWheelPos;
	
	Shader shader;
	World * world;
	Camera * cam;
	GLuint simpleShader;

	int init();
	int createWindow(int, int);

	void keyhandler();
	void mousehandler();
	void FPS(time_t &, int &, int &);
};

#endif