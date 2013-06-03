/*
*
*   AcceleratorEngine - libace
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#include "libace.h"

namespace ace {

Ace::Ace() {
    m_CurrentDirection = cfg::CAM_DIR_OFF;
    m_Wireframe = false;

    m_scenegraph = new Scenegraph();
}

Ace* Ace::getEngine() {
    static Ace instance;
    return &instance;
}

Scenegraph *Ace::Scene() {
    return m_scenegraph;
}

void Ace::renderScene( Shader& s ) {
    Camera  *c = Camera::getActive();
    s.bind();
    for( auto m : m_scenegraph->getObjects() ) {
        s.addUniform( "model", m->getTrafo() );
        s.addUniform( "proj", c->getProjectionMatrix() );
        s.addUniform( "view", c->getViewMatrix() );
        s.addUniform( "tex", m->getTextureId() );

        s.addAttribute( "in_uv", cfg::ACE_ATTRIB_UV );
        s.addAttribute( "in_vn", cfg::ACE_ATTRIB_NORM );
        s.addAttribute( "in_pos", cfg::ACE_ATTRIB_VERT );

        m->draw();
    }
}

void Ace::render() {
    GBuffer *g = GBuffer::getGBuffer();  
    g->render();
}

void Ace::nextDebugMode() {
    GBuffer *g = GBuffer::getGBuffer();
    g->nextDebugMode();
}

void Ace::start() {
    display();
}

int Ace::keyPressed( int key ) {
    return glfwGetKey( key );
}

void Ace::mouse() {
    Camera  *c = Camera::getActive();

    int x, y;
    glfwGetMousePos( &x, &y );

    glm::vec2 mousediff = glm::vec2( x - cfg::screenwidth / 2.0, y - cfg::screenheight / 2.0 );
    glm::normalize( mousediff );
    c->pitch( -mousediff.x * cfg::mouse_speed );
    c->yaw( mousediff.y * cfg::mouse_speed );

    glfwSetMousePos( cfg::screenwidth / 2.0, cfg::screenheight / 2.0 );
}

void Ace::keyboard() {
    m_extKeyboard();

    if( keyPressed( 'W' ) ) {
        m_CurrentDirection = cfg::CAM_DIR_FWD;
    }
    else if( keyPressed( 'S' ) ) {
        m_CurrentDirection = cfg::CAM_DIR_RWN;
    }
    else if( keyPressed( 'A' ) ) {
        m_CurrentDirection = cfg::CAM_DIR_LFT;
    }
    else if( keyPressed( 'D' ) ) {
        m_CurrentDirection = cfg::CAM_DIR_RGT;
    } 
    else if( keyPressed( 'F' ) ) {
        if( m_Wireframe ) {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); 
        } 
        else {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );             
        }
        m_Wireframe = !m_Wireframe;
    }
    else {
        m_CurrentDirection = cfg::CAM_DIR_OFF;        
    }

    mouse();
}

void Ace::display() {
    bool running          = true;
    double time_start     = glfwGetTime();
    int frames            = 0;
    std::string wnd_title = "AcceleratorEngine";

    while( running ) {
        Camera  *c = Camera::getActive();
        frames++;
        if( glfwGetTime() - time_start > 1.0 ) {
            time_start = glfwGetTime();
            std::stringstream oss;
            oss << wnd_title << " " << frames << " FPS";
            glfwSetWindowTitle( oss.str().c_str() );
            frames = 0;
        }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // camera
        if( m_CurrentDirection == cfg::CAM_DIR_FWD ) {
            c->move( cfg::cam_speed_fwd_rwn );
        }
        else if( m_CurrentDirection == cfg::CAM_DIR_RWN ) {
            c->move( -cfg::cam_speed_fwd_rwn );
        }
        else if( m_CurrentDirection == cfg::CAM_DIR_RGT ) {
            c->strafe( cfg::cam_speed_lft_rgt );
        }
        else if( m_CurrentDirection == cfg::CAM_DIR_LFT ) {
            c->strafe( -cfg::cam_speed_lft_rgt );
        }

        m_extDisplay();

        glfwSwapBuffers();
        running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
        keyboard();
    }

    // exit
    glfwTerminate();
}

void Ace::init( void ( *display )(), void ( *keyboard )() ) {
    m_extDisplay  = display;
    m_extKeyboard = keyboard;

    if( !glfwInit() ) {
        // Error
    }
    
    // force opengl 3.2 
#ifdef __MACH__
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
    glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
#endif

    if( !glfwOpenWindow( cfg::screenwidth, cfg::screenheight,
                         cfg::rgbbits, cfg::rgbbits, cfg::rgbbits, cfg::rgbbits,
                         cfg::depthbits, cfg::stencilbits,
                         cfg::fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW ) ) {
        glfwTerminate();
        // Error
    }

    glfwSetWindowTitle( "AcceleratorEngine" );

    // check if our stuff works on linux platforms
#ifndef __MACH__
    GLenum err = glewInit();
    
    if ( GLEW_OK != err ) {
      std::cout << "AcceleratorEngine ERROR: " << glewGetErrorString( err ) << std::endl;
    }
#endif

    // back face culling
    // glEnable( GL_CULL_FACE );
    // glCullFace( GL_BACK );

    // alpha blending
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // depth test
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glClearDepth( 1.0 );

    // glfwEnable( GLFW_STICKY_KEYS );
    glfwEnable( GLFW_KEY_REPEAT );
    glfwDisable( GLFW_MOUSE_CURSOR );
    glfwSetMousePos( cfg::screenwidth / 2.0, cfg::screenheight / 2.0 );
    // glfwSwapInterval( 1 ); // enable v-sync

    // camera
    glm::vec3 pos( 0, 1, 10 ); 
    glm::vec3 dir( 0, 0, -1 );
    glm::vec3 up( 0, 1, 0 );
    cam = new Camera(   pos, 
                        dir,
                        up, 
                        cfg::fov, 
                        cfg::aspectratio, 
                        1.0f, 
                        1000.0f );
}

}
