// OpenGL 
#ifdef __MACH__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GL/glfw.h>
#elif __linux__ 
    #include <GL/glew.h>
    #include <GL/glfw.h>
#endif