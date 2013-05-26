#include "World.hpp"

World::World() {

}

void World::init() {

	

}

void World::render() {

	for (std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++) {

		Object o = *it;

#ifdef __MACH__
		glBindVertexArrayAPPLE(o.vertexArray);
#elif
		glBindVertexArray(o.vertexArray);
#endif
		glDrawArrays(GL_TRIANGLES, 0, 3 * o.triangles);

	}

}

void World::addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
	
	Object o;

#ifdef __MACH__
	glGenVertexArraysAPPLE(1, &o.vertexArray);
	glBindVertexArrayAPPLE(o.vertexArray);
#elif
	glGenVertexArrays(1, &o.vertexArray);
	glBindVertexArray(o.vertexArray);
#endif

	o.vertexData = new GLfloat[9];
	for (int i = 0; i < 3; i++) {
		o.vertexData[i] = a[i];
		o.vertexData[i + 3] = b[i];
		o.vertexData[i + 6] = c[i];
	}


	glGenBuffers(1, &o.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, o.vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(o.vertexData), o.vertexData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	o.modelMatrix = glm::mat4(1.f);
	o.triangles = 1;

	objects.push_back(o);
	
}

void World::addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {

	Object o;

#ifdef __MACH__
	glGenVertexArraysAPPLE(1, &o.vertexArray);
	glBindVertexArrayAPPLE(o.vertexArray);
#elif
	glGenVertexArrays(1, &o.vertexArray);
	glBindVertexArray(o.vertexArray);
#endif

	o.vertexData = new GLfloat[18];
	for (int i = 0; i < 3; i++) {
		o.vertexData[i] = a[i];
		o.vertexData[i + 3] = b[i];
		o.vertexData[i + 6] = c[i];
		o.vertexData[i + 9] = c[i];
		o.vertexData[i + 12] = d[i];
		o.vertexData[i + 15] = a[i];
	}

	glGenBuffers(1, &o.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, o.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(o.vertexData), o.vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	o.modelMatrix = glm::mat4(1.f);
	o.triangles = 2;

	objects.push_back(o);

}