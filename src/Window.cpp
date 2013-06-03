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

    //glfwSwapInterval(0);

    simpleShader = shader.loadShaders( "../shader/SimpleVert.shader", "../shader/SimpleFrag.shader" );

    return 1;

}

void Window::initCam(int width, int height) {

    cam = new Camera(glm::vec3(400.f, 100.f, -200.f), glm::vec3(-1.f, -1.f, -1.f), glm::vec3(0.f, 1.f, 0.f),
        45.f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 10000.f);

}

void Window::loop() {

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(simpleShader);

    GLuint MatrixID = glGetUniformLocation(simpleShader, "MVP");
    GLuint LightID = glGetUniformLocation(simpleShader, "Light");
    world->setMVPLocation(MatrixID);
    world->setLightLocation(LightID);

    int frames = 0;
    time_t timer;
    time(&timer);
    int oldTime = timer;

    do{
        
        FPS(timer, oldTime, frames);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        keyhandler();
        mousehandler();

        world->render();
        
        glfwSwapBuffers();
     
    } while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

}

void Window::keyhandler() {

    if (glfwGetKey('W') == GLFW_PRESS) {
        cam->move(0.5, 0.0, 0.0);
    }
    if (glfwGetKey('S') == GLFW_PRESS) {
        cam->move(-0.5, 0.0, 0.0);
    }
    if (glfwGetKey('A') == GLFW_PRESS) {
        cam->move(0.0, -0.5, 0.0);
    }
    if (glfwGetKey('D') == GLFW_PRESS) {
        cam->move(0.0, 0.5, 0.0);
    }
    if (glfwGetKey('Q') == GLFW_PRESS) {
        cam->move(0.0, 0.0, 0.5);
    }
    if (glfwGetKey('E') == GLFW_PRESS) {
        cam->move(0.0, 0.0, -0.5);
    }

}

void Window::mousehandler() {

}

void Window::FPS(time_t &timer, int &oldTime, int &frames) {
    frames++;
    time(&timer);
    if (timer > oldTime) {
        cout << frames << " fps.\n";
        frames = 0;
    }
    oldTime = timer;
}