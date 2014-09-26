#ifndef _NORMALRENDER_
#define _NORMALRENDER_

#include "render.hpp"
#include "normalpass.hpp"
#include "../camera.hpp"

#include <set>

class NormalRender : public Render {

	public:

		NormalRender(Camera & cam) : m_cam(cam) {}

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_normalPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_normalPass.removeObject(id); }

		void changeBaseSize(unsigned int w, unsigned int h) { m_cam.resize(w, h); }

	private:

		Camera & m_cam;
		NormalPass m_normalPass;

};

#endif // _NORMALRENDER_