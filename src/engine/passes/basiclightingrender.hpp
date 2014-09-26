#ifndef _BASICLIGHTINGRENDER_
#define _BASICLIGHTINGRENDER_

#include "render.hpp"
#include "basiclightingpass.hpp"
#include "../camera.hpp"

#include <set>
#include <vector>
#include <memory>

class BasicLightingRender : public Render {

	public:

		BasicLightingRender(Camera & cam, std::vector<std::shared_ptr<Light>> lights) : m_cam(cam), m_lights(lights) {}

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_basicLightingPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_basicLightingPass.removeObject(id); }

		void changeBaseSize(unsigned int w, unsigned int h) { m_cam.resize(w, h); }

	private:

		Camera & m_cam;
		std::vector<std::shared_ptr<Light>> m_lights;
		BasicLightingPass m_basicLightingPass;

};

#endif // _BASICLIGHTINGRENDER_