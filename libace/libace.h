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

#include "camera.h"         // camera setup
#include "config.h"

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

    // Timer *m_Timer;

    Ace();
    Ace( const Ace& ) {};

public:

	/**
	* @brief Starting point: returns the singleton engine instance.
	*/
	static Ace* getInstance();

	Camera  *cam;

    int  AceKeyPressed( int key );
    void AceMouse();
    void AceKeyboard();
    void AceDisplay();
    void AceInit( void ( *display )(), void ( *keyboard )() );
    void AceMainLoop();

};

}

#endif // LIBACE_H