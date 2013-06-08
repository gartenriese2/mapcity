#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdio.h>
#include <time.h>
#include <sstream>

#include "World.hpp"
#include "Camera.hpp"
#include "Render.hpp"

using namespace glm;
using namespace std;

class Window {
public:
	Window(int, int);
	~Window();
	void initCam(int, int);
	void loop();
	inline Camera * getCam() { return m_cam; }
	inline void setWorld(World * world) { m_world = world; }
private:

	int m_width;
	int m_height;

	int m_mousePosX, m_mousePosY, m_mouseWheelPos;
	
	World * m_world;
	Camera * m_cam;
	Render * m_render;

	int init();
	int createWindow(int, int);

	void keyhandler();
	void mousehandler();
	void FPS(time_t &, int &, int &);
};

#endif