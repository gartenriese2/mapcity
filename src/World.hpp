#ifndef WORLD_HPP
#define WORLD_HPP

#include "ogl.h"
#include <vector>
#include "glm.h"
#include <iostream>
#include "Camera.hpp"

struct Object {
	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint colorBuffer;
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
	void addCuboid(glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	void addCuboid(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	void createCuboidData(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, GLfloat * &, GLfloat * &);
	inline std::vector<Object> getObjects() { return objects; }
	inline void setMVPLocation(GLuint mvp) { mvpID = mvp; }
	inline void setLightLocation(GLuint light) { lightID = light; }
	inline Camera& getCamera() { return this->cam; }
	
private:
	std::vector<Object> objects;
	Camera cam;
	GLuint mvpID;
	GLuint lightID;
};

#endif