#include "Window.hpp"

Window::Window(int width, int height) {
    
    m_height = height;
    m_width = width;

    if(init()) {
        createWindow(m_width, m_height);
    }

}

Window::~Window() {
    glfwCloseWindow();
    glfwTerminate();
}

int Window::init() {
    
    if(!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

#ifndef __MACH__
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    return 1;

}

int Window::createWindow(int width, int height) {

    m_height = height;
    m_width = width;

    if( !glfwOpenWindow( m_width, m_height, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        return -1;
    }

    glfwSetWindowTitle( "MapCity" );

#ifndef __MACH__
    glewExperimental=true;
    int err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
#endif

    glfwSwapInterval(0);

    return 1;

}

void Window::initCam(int width, int height) {

    m_cam = make_shared<Camera>(glm::vec3(400.f, 100.f, -200.f), glm::vec3(-1.f, -1.f, -1.f), glm::vec3(0.f, 1.f, 0.f),
        45.f, width, height, 0.1f, 10000.f);

}

void Window::loop() {

    m_render = make_shared<Render>();
    m_render->init();

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Time t;

    do{
        
        //FPS(t);

        keyhandler();
        mousehandler();

        // switch(option):
        // case
        //m_render->depthPlayerPass(* m_cam);
        // t.start();
        m_render->simplePass(* m_cam);
        // t.end();
        // m_render->depthLightPass(* m_cam);
        
        // m_render->gbufferPass(* m_cam);
        // m_render->simpleTexPass();
        
        //t.waitAndAdd();
        glfwSwapBuffers();
     
    } while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

}

void Window::keyhandler() {

    if (glfwGetKey('W') == GLFW_PRESS) {
        m_cam->move(1.f, 0.0, 0.0);
    }
    if (glfwGetKey('S') == GLFW_PRESS) {
        m_cam->move(-1.f, 0.0, 0.0);
    }
    if (glfwGetKey('A') == GLFW_PRESS) {
        m_cam->move(0.0, -1.f, 0.0);
    }
    if (glfwGetKey('D') == GLFW_PRESS) {
        m_cam->move(0.0, 1.f, 0.0);
    }
    if (glfwGetKey('Q') == GLFW_PRESS) {
        m_cam->move(0.0, 0.0, 1.f);
    }
    if (glfwGetKey('E') == GLFW_PRESS) {
        m_cam->move(0.0, 0.0, -1.f);
    }
    if (glfwGetKey('R') == GLFW_PRESS) {
        m_cam->reset();
    }
    if (glfwGetKey(GLFW_KEY_INSERT) == GLFW_PRESS) {
        m_cam->rotateAround(0.4f);
    }
    if (glfwGetKey(GLFW_KEY_DEL) == GLFW_PRESS) {
        m_cam->rotateAround(-0.4f);
    }

}

void Window::mousehandler() {

    if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        
        int newX, newY;
        glfwGetMousePos(&newX, &newY);

        if (m_mousePosX != newX || m_mousePosY != newY) {
            
            m_cam->rotate(static_cast<float>(m_mousePosX-newX), static_cast<float>(m_mousePosY-newY));
            m_mousePosX = newX;
            m_mousePosY = newY;

        }

    } else {
        glfwGetMousePos(&m_mousePosX, &m_mousePosY);
    }

    int i = glfwGetMouseWheel();
    if (i != m_mouseWheelPos) {
        m_cam->zoom(i - m_mouseWheelPos);
        m_mouseWheelPos = i;
    }

}

void Window::FPS(Time & t) {

    std::stringstream oss;
    oss << "MapCity: " << t.getAverage() << " ms.";
    glfwSetWindowTitle(oss.str().c_str());
    
}