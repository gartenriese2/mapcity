#ifndef _BASICRENDER_
#define _BASICRENDER_

#include "render.hpp"
#include "basicpass.hpp"
#include "../camera.hpp"

#include <set>

class BasicRender : public Render {

	public:

		BasicRender(Camera & cam) : m_cam(cam) {}

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_basicPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_basicPass.removeObject(id); }

		void changeBaseSize(unsigned int w, unsigned int h) { m_cam.resize(w, h); }

	private:

		Camera & m_cam;
		BasicPass m_basicPass;

};

#endif // _BASICRENDER_