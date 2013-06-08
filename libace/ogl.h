// OpenGL 
#ifdef __MACH__
    #include <GL/glfw.h>
    #include <OpenGL/gl3.h>
#elif __linux__ 
	#define GLEW_STATIC
    #include <GL/glew.h>
    #include <GL/glfw.h>
#endif