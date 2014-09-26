#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdio.h>
#include <time.h>
#include <sstream>
#include <memory>

#include "Camera.hpp"
#include "Render.hpp"
#include "Timer.hpp"
#include "Time.hpp"
#include "InputHandler.hpp"

using namespace glm;
using namespace std;

class Window {
	
	public:
		
		Window(const int, const int);
		~Window();

		void initCam(const int, const int);
		void loop();
		const shared_ptr<Camera> & getCam() const { return m_cam; }
	
	private:

		int m_width;
		int m_height;

		int m_mousePosX, m_mousePosY, m_mouseWheelPos;
		bool m_clickRight = false, m_clickLeft = false, m_clicked = false;
		
		shared_ptr<Camera> m_cam;
		shared_ptr<Render> m_render;

		bool m_infoMode = true;

		int init() const;
		int createWindow(const int, const int);

		void keyhandler() const;
		void mousehandler();
		void FPS(Timer &) const;

};

#endif