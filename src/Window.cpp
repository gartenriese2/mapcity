#include "Window.hpp"

Window::Window(int height, int width) {
    
    m_height = height;
    m_width = width;



    if(init()) {
        createWindow(m_height, m_width);
    }

    world.init();

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

    simpleShader = shader.loadShaders( "../shader/SimpleVert.shader", "../shader/SimpleFrag.shader" );

    return 1;

}

void Window::loop() {

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(simpleShader);

    GLuint MatrixID = glGetUniformLocation(simpleShader, "MVP");
    GLuint LightID = glGetUniformLocation(simpleShader, "Light");
    world.setMVPLocation(MatrixID);
    world.setLightLocation(LightID);

    do{
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        keyhandler();
        mousehandler();

        world.render();
        
        glfwSwapBuffers();
     
    } while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

}

void Window::keyhandler() {

    if (glfwGetKey('W') == GLFW_PRESS) {
        world.getCamera().move(0.01, 0.0, 0.0);
    }
    if (glfwGetKey('S') == GLFW_PRESS) {
        world.getCamera().move(-0.01, 0.0, 0.0);
    }
    if (glfwGetKey('A') == GLFW_PRESS) {
        world.getCamera().move(0.0, -0.01, 0.0);
    }
    if (glfwGetKey('D') == GLFW_PRESS) {
        world.getCamera().move(0.0, 0.01, 0.0);
    }
    if (glfwGetKey('Q') == GLFW_PRESS) {
        world.getCamera().move(0.0, 0.0, 0.01);
    }
    if (glfwGetKey('E') == GLFW_PRESS) {
        world.getCamera().move(0.0, 0.0, -0.01);
    }

}

void Window::mousehandler() {

}