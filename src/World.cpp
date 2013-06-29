#include "World.hpp"

long counter  = 0;

World::World(const int height, const int width) {
	
	m_map = std::make_shared<Map>(height, width);
	
}

/**
 * adds a triangle to the object vector
 * @param a   first point
 * @param b   second point (anticlockwise)
 * @param c   third point (anticlockwise)
 * @param col optional color
 */
void World::addTriangle(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::TRIANGLE, a, b, c, col));
	
}

/**
 * adds a quad to the object vector
 * @param a   first point
 * @param b   second point (anticlockwise)
 * @param d   fourth point (anticlockwise)
 * @param col optional color
 */
void World::addQuad(const glm::vec3 a, const glm::vec3 b, const glm::vec3 d, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::QUAD, a, b, d, col));

}

/**
 * adds a quad to the object vector
 * @param start midpoint of the left side
 * @param end   midpoint of the right side
 * @param width length of left/right side
 * @param col   optional color
 */
void World::addQuad(const glm::vec3 start, const glm::vec3 end, const float width, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::QUAD, start, end, width, col));

}

/**
 * adds a quad to the object vector
 * @param start      midpoint of left side
 * @param end        midpoint of right side
 * @param widthStart length of left side
 * @param widthEnd   length of right side
 * @param col        optional color
 */
void World::addQuad(const glm::vec3 start, const glm::vec3 end, const float widthStart, const float widthEnd, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::QUAD, start, end, widthStart, widthEnd, col));

}

/**
 * adds a hexagon to the object vector
 * @param center center of the hexagon
 * @param left   left point of the hexagon
 * @param col    optional color
 */
void World::addHexagon(const glm::vec3 center, const glm::vec3 left, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::HEXAGON, center, left, col));

}

/**
 * adds a cuboid to the object vector
 * @param a   [description]
 * @param b   [description]
 * @param c   [description]
 * @param d   [description]
 * @param col [description]
 */
void World::addCuboid(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::CUBOID, a, b, c, d, col));

}

void World::addCuboid(const glm::vec3 center, const glm::vec3 dirX, const glm::vec3 dirZ, const float height, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::CUBOID, center, dirX, dirZ, height, col));

}

void World::addSpline(std::vector<glm::vec3> pts, const float width, const glm::vec3 col) {

	m_objects.push_back(Object(ObjectType::SPLINE, pts, width, col));
	
}