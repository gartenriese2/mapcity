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
	static Ace* getEngine();

	Camera  *cam;

    int  keyPressed( int key );
    void mouse();
    void keyboard();
    void display();
    void init( void ( *display )(), void ( *keyboard )() );
    void start();

};

class Renderblock {
private:
    GBuffer *g;
    Ace     *a;
public:
    Renderblock() { 
        g = GBuffer::getGBuffer();
        a = Ace::getEngine();
        g->startRecording();
    }
    void draw( Mesh& m ) {
        int loc = 0;

        loc = glGetUniformLocation( g->getRecShader()->getId(), "model" );
        glUniformMatrix4fv( loc, 1, GL_FALSE, glm::value_ptr( m.getTrafo() ) ) ;

        loc = glGetUniformLocation( g->getRecShader()->getId(), "proj" );
        glUniformMatrix4fv( loc, 1, GL_FALSE, glm::value_ptr( a->cam->getProjectionMatrix() ) );
            
        loc = glGetUniformLocation( g->getRecShader()->getId(), "view" );
        glUniformMatrix4fv( loc, 1, GL_FALSE, glm::value_ptr( a->cam->getViewMatrix() ) );

        //loc = glGetUniformLocation( g->getRecShader()->getId(), "tex" );
        //glUniform1i( loc, tex1->getId() );   

        glBindAttribLocation( g->getRecShader()->getId(), cfg::ACE_ATTRIB_UV, "in_uv" );
        glBindAttribLocation( g->getRecShader()->getId(), cfg::ACE_ATTRIB_NORM, "in_vn" );
        glBindAttribLocation( g->getRecShader()->getId(), cfg::ACE_ATTRIB_VERT, "in_pos" );

        m.draw();
    }
    ~Renderblock() {
        g->stopRecording();
        g->render();
    }
};

}

#endif // LIBACE_H