#ifndef RENDER_HPP
#define RENDER_HPP

#include "ogl.h"
#include "World.hpp"
#include "Shader.hpp"
#include "Fbo.hpp"
#include <iostream>

class Render {
public:
	Render(World *);
	~Render();

	void init();
	void simplePass(Camera &);
	void depthPlayerPass(Camera &);
	void depthLightPass(Camera &);
	
private:
	World * m_world;
	Fbo * m_fbo;

	Shader * m_simpleShader;
	GLuint m_MVP_simplePass;
	GLuint m_Light_simplePass;

	Shader * m_depthShader;
	GLuint m_MVP_depthPass;
	int m_depthTextureWidth;
	int m_depthTextureHeight;
};

#endif
