// OpenGL 
#ifdef __MACH__
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
    #include <GL/glfw.h>
#elif __linux__ 
    #include <GL/glew.h>
    #include <GL/glfw.h>
#endif