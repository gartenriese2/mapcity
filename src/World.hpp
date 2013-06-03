#ifndef WORLD_HPP
#define WORLD_HPP

#include "ogl.h"
#include <vector>
#include "glm.h"
#include <iostream>
#include "Camera.hpp"
#include "Object.hpp"

#include "Map.hpp"

class World {
public:
	World(int, int);
	void createMap(int, int);

	void render();

	void addTriangle(glm::vec3, glm::vec3, glm::vec3, glm::vec3 col = glm::vec3(1,1,1));
	void addQuad(glm::vec3, glm::vec3, glm::vec3, glm::vec3 col = glm::vec3(1,1,1));
	void addHexagon(glm::vec3, glm::vec3, glm::vec3 col = glm::vec3(1,1,1));
	void addCuboid(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3 col = glm::vec3(1,1,1));
	
	void createCuboidData(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, GLfloat * &, GLfloat * &, GLushort * &);

	inline std::vector<Object> getObjects() { return objects; }
	inline void setMVPLocation(GLuint mvp) { mvpID = mvp; }
	inline void setLightLocation(GLuint light) { lightID = light; }
	inline void setCamera(Camera * c) { cam = c; }
	
private:
	
	std::vector<Object> objects;
	Camera * cam;
	Map * map;

	GLuint mvpID;
	GLuint lightID;
};

#endif