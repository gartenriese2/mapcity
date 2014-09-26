#ifndef _GBUFFERRENDER_
#define _GBUFFERRENDER_

#include "render.hpp"

#include "gbufferpass.hpp"
#include "../gl/fbo.hpp"
#include "../gl/texture.hpp"
#include "../camera.hpp"

class GBufferRender : public Render {

	public:

		GBufferRender(Camera & cam);

		void draw();

		void addObjects(std::set<unsigned long> vec) { m_gbufferPass.addObjects(vec); }
		void removeObject(unsigned long id) { m_gbufferPass.removeObject(id); }

		void changeBaseSize(unsigned int w, unsigned int h);

	private:

		Camera & m_cam;
		gl::FBO m_fbo;
		gl::Texture m_colorTex;
		gl::Texture m_depthTex;
		gl::Texture m_normalTex;
		gl::Texture m_positionTex;
		gl::Texture m_depthAttachment;
		GBufferPass m_gbufferPass;

};

#endif // _GBUFFERRENDER_
