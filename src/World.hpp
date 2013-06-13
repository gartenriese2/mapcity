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
	World(const int, const int);
	void createMap(const int, const int);

	void addTriangle(const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void addQuad(const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void addQuad(const glm::vec3, const glm::vec3, const float, const glm::vec3 col = glm::vec3(1,1,1));
	void addHexagon(const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void addCuboid(const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3, const glm::vec3 col = glm::vec3(1,1,1));
	void addCuboid(const glm::vec3, const glm::vec3, const glm::vec3, const float, const glm::vec3 col = glm::vec3(1,1,1));
	void addSpline(std::vector<glm::vec3>, const float, const glm::vec3 col = glm::vec3(1,1,1));
	
	void createCuboidData(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, GLfloat * &, GLfloat * &, GLushort * &);
	glm::vec3 drawBezier(glm::vec3, glm::vec3, glm::vec3, glm::vec3, float);
	glm::vec3 drawHermite(glm::vec3, glm::vec3, glm::vec3, glm::vec3, float);

	inline std::vector<Object> & getObjects() { return m_objects; }
	
private:
	
	std::vector<Object> m_objects;
	Map * m_map;

};

#endif