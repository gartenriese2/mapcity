/*
*
*	AcceleratorEngine - libace
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#ifndef LIBACE_H
#define LIBACE_H

#include "ogl.h"
#include "stl.h"
#include "glm.h"

#include "camera.h"
#include "config.h"
#include "mesh.h"
#include "error.h"
#include "shader.h"
#include "object.h"
#include "gbuffer.h"
#include "texture.h"
#include "scenegraph.h"
#include "light.h"

namespace ace {

/**
*	@class Ace
*
*	@brief Singleton class which represents the whole engine.
*/
class Ace {

private: 

	void ( *m_extDisplay )();
    void ( *m_extKeyboard )();

    // global functions
    int   m_CurrentDirection;
    bool  m_Wireframe;
    int   m_Frames;

    Scenegraph *m_scenegraph;

    // Timer *m_Timer;

    Ace();
    Ace( const Ace& ) {};

public:

	/**
	* @brief Starting point: returns the singleton engine instance.
	*/
	static Ace* getEngine();

	Camera  *cam;

    Scenegraph *Scene();

    int  keyPressed( int key );
    void mouse();
    void keyboard();
    void display();
    void init( void ( *display )(), void ( *keyboard )() );
    void start();
    void render();
    void nextDebugMode();
};

}

#endif // LIBACE_H