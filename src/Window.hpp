#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdio.h>
#include <time.h>
#include <sstream>
#include <memory>

#include "World.hpp"
#include "Camera.hpp"
#include "Render.hpp"
#include "Time.hpp"

using namespace glm;
using namespace std;

class Window {
public:
	Window(int, int);
	~Window();
	void initCam(int, int);
	void loop();
	inline shared_ptr<Camera> getCam() { return m_cam; }
	inline void setWorld(shared_ptr<World> world) { m_world = world; }
private:

	int m_width;
	int m_height;

	int m_mousePosX, m_mousePosY, m_mouseWheelPos;
	
	shared_ptr<World> m_world;
	shared_ptr<Camera> m_cam;
	shared_ptr<Render> m_render;

	int init();
	int createWindow(int, int);

	void keyhandler();
	void mousehandler();
	void FPS(Time &);
};

#endif