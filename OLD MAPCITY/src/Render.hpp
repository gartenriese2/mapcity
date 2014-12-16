#ifndef RENDER_HPP
#define RENDER_HPP

#include "glincludes.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Fbo.hpp"
#include "ObjectContainer.hpp"
#include "InputHandler.hpp"
#include <iostream>
#include <memory>

class Render {
	
	public:
		
		Render();
		~Render();

		void init();
		void simplePass(const Camera &) const;
		void gbufferPass(const Camera &) const;
		void gbufferClickPass(const Camera &, const unsigned int, const unsigned int, const bool) const;

		void simpleTexPass(const Camera &) const;
		void depthPlayerPass(const Camera &) const;
		void depthLightPass(const Camera &) const;
		void shadowPass(const Camera &) const;
		
	private:
		
		std::shared_ptr<Fbo> m_fbo;

		std::shared_ptr<Shader> m_simpleShader;
		GLint m_MVP_simplePass;
		GLint m_Light_simplePass;

		std::shared_ptr<Shader> m_depthShader;
		GLint m_MVP_depthPass;
		int m_depthTextureWidth;
		int m_depthTextureHeight;
		std::shared_ptr<Camera> m_lightCam;

		std::shared_ptr<Shader> m_shadowShader;
		glm::mat4 m_shadowBiasMatrix;
		//GLuint m_MVP_shadowPass;
		//GLuint m_depthMVP_shadowPass;
		GLuint m_shadowTexture;

		std::shared_ptr<Shader> m_gbufferShader;
		GLint m_MVP_gbufferPass;
		GLint m_depthBiasMVP_gbufferPass;
		GLint m_Light_gbufferPass;
		GLuint m_gbufferPositionTexture;
		GLuint m_gbufferNormalTexture;
		GLuint m_gbufferDepthTexture;
		GLuint m_gbufferColorTexture;
		GLuint m_gbufferShadowTexture;

		std::shared_ptr<Shader> m_simpleTexShader;
		Object m_screenSizedQuad;
		GLuint m_projMat;

};

#endif