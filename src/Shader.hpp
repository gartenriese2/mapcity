#ifndef SHADER_HPP
#define SHADER_HPP

#include "ogl.h"
#include "glm.h"

#include <iostream>
#include <fstream>
#include <vector>

class Shader {
public:
	Shader();
	GLuint loadShaders(const char *,const char *);
private:
	
};

#endif
