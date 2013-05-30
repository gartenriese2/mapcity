#include "World.hpp"

long counter  = 0;

World::World() {

}

void World::init(int width, int height) {

	cam = Camera(glm::vec3(10.f, 10.f, 10.f), glm::vec3(-1.f, -1.f, -1.f), glm::vec3(0.f, 1.f, 0.f),
		45.f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.f);

}

void World::render() {

	for (std::vector<Object>::iterator o = objects.begin(); o != objects.end(); o++) {

		glBindVertexArray(o->vertexArray);

		glm::mat4 MVP = cam.getProjMat() * cam.getViewMat() * o->modelMatrix;
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
		glUniform3f(lightID, glm::sin(static_cast<float>(counter) / 1000.0) * 10,
							glm::abs(glm::cos(static_cast<float>(counter) / 1000.0)) * 10,
							0);
		glDrawArrays(GL_TRIANGLES, 0, 3 * o->triangles);

	}

	counter++;

}

void World::addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 col) {
	
	Object o;

	GLfloat * vertexData = new GLfloat[9];
	for (int i = 0; i < 3; i++) {
		vertexData[i] = a[i];
		vertexData[i + 3] = b[i];
		vertexData[i + 6] = c[i];
	}

	GLfloat * normalData = new GLfloat[9];
	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));
	for (int i = 0; i < 3; i++)	{
		normalData[i] = n[i];
		normalData[i + 3] = n[i];
		normalData[i + 6] = n[i];
	}

	GLfloat * colorData = new GLfloat[9];
	for (int i = 0; i < 9; i += 3) {
		colorData[i] = col[0];
		colorData[i + 1] = col[1];
		colorData[i + 2] = col[2];
	}

	fillBuffers(o, 9, vertexData, normalData, colorData);

	o.modelMatrix = glm::mat4(1.f);
	o.triangles = 1;

	objects.push_back(o);
	
}

void World::addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 col) {

	Object o;

	GLfloat * vertexData = new GLfloat[18];
	for (int i = 0; i < 3; i++) {
		vertexData[i] = a[i];
		vertexData[i + 3] = b[i];
		vertexData[i + 6] = c[i];
		vertexData[i + 9] = c[i];
		vertexData[i + 12] = d[i];
		vertexData[i + 15] = a[i];
	}

	GLfloat * normalData = new GLfloat[18];
	glm::vec3 n1 = glm::normalize(glm::cross(c - b, a - b));
	glm::vec3 n2 = glm::normalize(glm::cross(d - a, d - c));
	for (int i = 0; i < 3; i++) {
		normalData[i] = n1[i];
		normalData[i + 3] = n1[i];
		normalData[i + 6] = n1[i];
		normalData[i + 9] = n2[i];
		normalData[i + 12] = n2[i];
		normalData[i + 15] = n2[i];
	}

	GLfloat * colorData = new GLfloat[18];
	for (int i = 0; i < 18; i += 3) {
		colorData[i] = col[0];
		colorData[i + 1] = col[1];
		colorData[i + 2] = col[2];
	}

	fillBuffers(o, 18, vertexData, normalData, colorData);

	o.modelMatrix = glm::mat4(1.f);
	o.triangles = 2;

	objects.push_back(o);

}

void World::addCuboid(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 col) {

	Object o;
	
	GLfloat * vertexData;
	GLfloat * normalData;
	createCuboidData(a, b, c, d, vertexData, normalData);

	GLfloat * colorData = new GLfloat[6*18];
	for (int i = 0; i < 6*18; i += 3) {
		colorData[i] = col[0];
		colorData[i + 1] = col[1];
		colorData[i + 2] = col[2];
	}

	fillBuffers(o, 6*18, vertexData, normalData, colorData);

	o.modelMatrix = glm::mat4(1.f);
	o.triangles = 12;

	objects.push_back(o);

}

void World::createCuboidData(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const glm::vec3 &d, GLfloat * &vertexData, GLfloat * &normalData) {
	
	vertexData = new GLfloat[6*18];
	normalData = new GLfloat[6*18];

	glm::vec3 e = c + (b - a);
	glm::vec3 f = d + (c - a);
	glm::vec3 g = e + (d - a);
	glm::vec3 h = g + (a - c);
	glm::vec3 n1 = glm::normalize(glm::cross(a - b, c - b));
	glm::vec3 n2 = glm::normalize(glm::cross(d - a, f - a));
	glm::vec3 n3 = glm::normalize(glm::cross(c - e, f - e));

	for (int i = 0; i < 3; i++) {
		
		vertexData[i] = a[i];
		vertexData[i + 3] = b[i];
		vertexData[i + 6] = c[i];
		normalData[i] = n1[i];
		normalData[i + 3] = n1[i];
		normalData[i + 6] = n1[i];

		vertexData[i + 9] = c[i];
		vertexData[i + 12] = b[i];
		vertexData[i + 15] = e[i];
		normalData[i + 9] = n1[i];
		normalData[i + 12] = n1[i];
		normalData[i + 15] = n1[i];

		vertexData[i + 18] = a[i];
		vertexData[i + 21] = c[i];
		vertexData[i + 24] = f[i];
		normalData[i + 18] = n2[i];
		normalData[i + 21] = n2[i];
		normalData[i + 24] = n2[i];

		vertexData[i + 27] = f[i];
		vertexData[i + 30] = d[i];
		vertexData[i + 33] = a[i];
		normalData[i + 27] = n2[i];
		normalData[i + 30] = n2[i];
		normalData[i + 33] = n2[i];

		vertexData[i + 36] = c[i];
		vertexData[i + 39] = e[i];
		vertexData[i + 42] = f[i];
		normalData[i + 36] = n3[i];
		normalData[i + 39] = n3[i];
		normalData[i + 42] = n3[i];

		vertexData[i + 45] = f[i];
		vertexData[i + 48] = e[i];
		vertexData[i + 51] = g[i];
		normalData[i + 45] = n3[i];
		normalData[i + 48] = n3[i];
		normalData[i + 51] = n3[i];

		vertexData[i + 54] = a[i];
		vertexData[i + 57] = d[i];
		vertexData[i + 60] = b[i];
		normalData[i + 54] = -n3[i];
		normalData[i + 57] = -n3[i];
		normalData[i + 60] = -n3[i];
		
		vertexData[i + 63] = b[i];
		vertexData[i + 66] = d[i];
		vertexData[i + 69] = h[i];
		normalData[i + 63] = -n3[i];
		normalData[i + 66] = -n3[i];
		normalData[i + 69] = -n3[i];

		vertexData[i + 72] = e[i];
		vertexData[i + 75] = b[i];
		vertexData[i + 78] = g[i];
		normalData[i + 72] = -n2[i];
		normalData[i + 75] = -n2[i];
		normalData[i + 78] = -n2[i];

		vertexData[i + 81] = g[i];
		vertexData[i + 84] = b[i];
		vertexData[i + 87] = h[i];
		normalData[i + 81] = -n2[i];
		normalData[i + 84] = -n2[i];
		normalData[i + 87] = -n2[i];

		vertexData[i + 90] = f[i];
		vertexData[i + 93] = g[i];
		vertexData[i + 96] = h[i];
		normalData[i + 90] = -n1[i];
		normalData[i + 93] = -n1[i];
		normalData[i + 96] = -n1[i];
		
		vertexData[i + 99] = f[i];
		vertexData[i + 102] = h[i];
		vertexData[i + 105] = d[i];
		normalData[i + 99] = -n1[i];
		normalData[i + 102] = -n1[i];
		normalData[i + 105] = -n1[i];

	}

}

void World::fillBuffers(Object &o, int size, GLfloat * &vertexData, GLfloat * &normalData, GLfloat * &colorData) {

	glGenVertexArrays(1, &o.vertexArray);
	glBindVertexArray(o.vertexArray);

	glGenBuffers(1, &o.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, o.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &o.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, o.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, normalData, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &o.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, o.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, colorData, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

}