#include "Window.hpp"

Window::Window(int height, int width) {
    
    m_height = height;
    m_width = width;



    if(init()) {
        createWindow(m_height, m_width);
    }

    world.init(height, width);

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

void Window::loop() {

    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUseProgram(simpleShader);

    GLuint MatrixID = glGetUniformLocation(simpleShader, "MVP");
    GLuint LightID = glGetUniformLocation(simpleShader, "Light");
    world.setMVPLocation(MatrixID);
    world.setLightLocation(LightID);

    int frames = 0;
    time_t timer;
    time(&timer);
    int oldTime = timer;

    ////////////////////////////////////////////////

    // glm::vec3 a(-1,0,0), b(1,0,0), c(0,0,-1);
    // GLfloat * vertexData = new GLfloat[9];
    // for (int i = 0; i < 3; i++) {
    //     vertexData[i] = a[i];
    //     vertexData[i + 3] = b[i];
    //     vertexData[i + 6] = c[i];
    // }

    // GLfloat * normalData = new GLfloat[9];
    // glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));
    // for (int i = 0; i < 3; i++) {
    //     normalData[i] = n[i];
    //     normalData[i + 3] = n[i];
    //     normalData[i + 6] = n[i];
    // }

    // glm::vec3 col(1,0,0);
    // GLfloat * colorData = new GLfloat[9];
    // for (int i = 0; i < 9; i += 3) {
    //     colorData[i] = col[0];
    //     colorData[i + 1] = col[1];
    //     colorData[i + 2] = col[2];
    // }

    // GLushort * indexData = new GLushort[3];
    // indexData[0] = 0;
    // indexData[1] = 1;
    // indexData[2] = 2;

    // GLuint vertexArray;
    // glGenVertexArrays(1, &vertexArray);
    // glBindVertexArray(vertexArray);

    // GLuint vertexBuffer;
    // glGenBuffers(1, &vertexBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, vertexData, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glEnableVertexAttribArray(0);

    // GLuint normalBuffer;
    // glGenBuffers(1, &normalBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, normalData, GL_STATIC_DRAW);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glEnableVertexAttribArray(1);

    // GLuint colorBuffer;
    // glGenBuffers(1, &colorBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, colorData, GL_STATIC_DRAW);

    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glEnableVertexAttribArray(2);

    // GLuint indexBuffer;
    // glGenBuffers(1, &indexBuffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3, indexData, GL_STATIC_DRAW);

    // //////////////////////////

    // glm::vec3 a2(-1,0,2), b2(1,0,2), c2(0,0,1);
    // GLfloat * vertexData2 = new GLfloat[9];
    // for (int i = 0; i < 3; i++) {
    //     vertexData2[i] = a2[i];
    //     vertexData2[i + 3] = b2[i];
    //     vertexData2[i + 6] = c2[i];
    // }

    // GLfloat * normalData2 = new GLfloat[9];
    // glm::vec3 n2 = glm::normalize(glm::cross(c2 - b2, a2 - b2));
    // for (int i = 0; i < 3; i++) {
    //     normalData2[i] = n2[i];
    //     normalData2[i + 3] = n2[i];
    //     normalData2[i + 6] = n2[i];
    // }

    // glm::vec3 col2(1,0,0);
    // GLfloat * colorData2 = new GLfloat[9];
    // for (int i = 0; i < 9; i += 3) {
    //     colorData2[i] = col2[0];
    //     colorData2[i + 1] = col2[1];
    //     colorData2[i + 2] = col2[2];
    // }

    // GLushort * indexData2 = new GLushort[3];
    // indexData2[0] = 0;
    // indexData2[1] = 1;
    // indexData2[2] = 2;

    // GLuint vertexArray2;
    // glGenVertexArrays(1, &vertexArray2);
    // glBindVertexArray(vertexArray2);

    // GLuint vertexBuffer2;
    // glGenBuffers(1, &vertexBuffer2);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer2);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, vertexData2, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glEnableVertexAttribArray(0);

    // GLuint normalBuffer2;
    // glGenBuffers(1, &normalBuffer2);
    // glBindBuffer(GL_ARRAY_BUFFER, normalBuffer2);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, normalData2, GL_STATIC_DRAW);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glEnableVertexAttribArray(1);

    // GLuint colorBuffer2;
    // glGenBuffers(1, &colorBuffer2);
    // glBindBuffer(GL_ARRAY_BUFFER, colorBuffer2);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, colorData2, GL_STATIC_DRAW);

    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glEnableVertexAttribArray(2);

    // GLuint indexBuffer2;
    // glGenBuffers(1, &indexBuffer2);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer2);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3, indexData2, GL_STATIC_DRAW);

    ////////////////////////////////////////////////

    do{
        
        FPS(timer, oldTime, frames);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        keyhandler();
        mousehandler();

        /////////////////////////////////////////////

        // glBindVertexArray(vertexArray);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        // glm::mat4 MVP = world.getCamera().getProjMat() * world.getCamera().getViewMat();
        // glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        // glUniform3f(LightID, 5, 10, 0);

        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);


        // glBindVertexArray(vertexArray2);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer2);

        // glm::mat4 MVP2 = world.getCamera().getProjMat() * world.getCamera().getViewMat();
        // glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
        // glUniform3f(LightID, 5, 10, 0);

        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void*)0);

        /////////////////////////////////////////////

        world.render();
        
        glfwSwapBuffers();
     
    } while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

}

void Window::keyhandler() {

    if (glfwGetKey('W') == GLFW_PRESS) {
        world.getCamera().move(0.02, 0.0, 0.0);
    }
    if (glfwGetKey('S') == GLFW_PRESS) {
        world.getCamera().move(-0.02, 0.0, 0.0);
    }
    if (glfwGetKey('A') == GLFW_PRESS) {
        world.getCamera().move(0.0, -0.02, 0.0);
    }
    if (glfwGetKey('D') == GLFW_PRESS) {
        world.getCamera().move(0.0, 0.02, 0.0);
    }
    if (glfwGetKey('Q') == GLFW_PRESS) {
        world.getCamera().move(0.0, 0.0, 0.02);
    }
    if (glfwGetKey('E') == GLFW_PRESS) {
        world.getCamera().move(0.0, 0.0, -0.02);
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