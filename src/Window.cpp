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

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glewExperimental=true;
    int err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    return 1;

}

void Window::loop() {

    GLuint simpleShader = shader.loadShaders( "../shader/SimpleVert.shader", "../shader/SimpleFrag.shader" );

    do{
        
        // DRAW

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1,1,1,1);

        glUseProgram(simpleShader);

        world.render();
        
        glfwSwapBuffers();
     
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
    glfwGetWindowParam( GLFW_OPENED ) );

}