#ifndef WORLD_HPP
#define WORLD_HPP

#include "ogl.h"
#include <vector>
#include "glm.h"
#include <iostream>

struct Object {
	GLfloat * vertexData;
	GLuint vertexBuffer;
	GLuint vertexArray;
	int triangles;
	glm::mat4 modelMatrix;
};

class World {
public:
	World();

	void init();
	void render();
	void addTriangle(glm::vec3, glm::vec3, glm::vec3);
	void addQuad(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	inline std::vector<Object> getObjects() { return objects; }
	
private:
	std::vector<Object> objects;
};

#endif
