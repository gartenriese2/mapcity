#include "World.hpp"

long counter  = 0;

World::World(int height, int width) {
	createMap(height, width);
}

void World::createMap(int height, int width) {
	map = new Map(height, width);

	std::vector<Hexagon> v = map->getHexaVector();
	for (std::vector<Hexagon>::iterator h = v.begin(); h != v.end(); ++h) {
		addHexagon(h->getCenter(), h->getLeft());
	}
}

void World::addTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 col) {
	
	Object o = Object();

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

	GLushort * indexData = new GLushort[3];
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;

	o.fillBuffers(9, 3, vertexData, normalData, colorData, indexData);

	o.setTriangles(1);

	objects.push_back(o);
	
}

void World::addQuad(glm::vec3 a, glm::vec3 b, glm::vec3 d, glm::vec3 col) {

	Object o = Object();

	glm::vec3 c = b + (d - a);

	GLfloat * vertexData = new GLfloat[12];
	for (int i = 0; i < 3; i++) {
		vertexData[i] = a[i];
		vertexData[i + 3] = b[i];
		vertexData[i + 6] = c[i];
		vertexData[i + 9] = d[i];
	}

	GLfloat * normalData = new GLfloat[12];
	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));
	for (int i = 0; i < 3; i++) {
		normalData[i] = n[i];
		normalData[i + 3] = n[i];
		normalData[i + 6] = n[i];
		normalData[i + 9] = n[i];
	}

	GLfloat * colorData = new GLfloat[12];
	for (int i = 0; i < 12; i += 3) {
		colorData[i] = col[0];
		colorData[i + 1] = col[1];
		colorData[i + 2] = col[2];
	}

	GLushort * indexData = new GLushort[6];
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	indexData[3] = 2;
	indexData[4] = 3;
	indexData[5] = 0;

	o.fillBuffers(12, 6, vertexData, normalData, colorData, indexData);

	o.setTriangles(2);

	objects.push_back(o);

}

void World::addHexagon(glm::vec3 center, glm::vec3 left, glm::vec3 col) {

	Object o = Object();

	GLfloat * vertexData = new GLfloat[21];
	GLfloat * normalData = new GLfloat[21];
	GLfloat * colorData = new GLfloat[21];

	glm::vec3 side = left - center;
	float factor = glm::sqrt((glm::pow(side.x, 2.f) + glm::pow(side.y, 2.f) + glm::pow(side.z, 2.f)) * 3.f) / 2.f;
	glm::vec3 up = glm::normalize(glm::vec3(side.z, 0, side.x));
	up *= factor;
	
	glm::vec3 upperleft = center + side / 2.f + up;
	glm::vec3 upperright = center - side / 2.f + up;
	glm::vec3 right = center - side;
	glm::vec3 lowerright = center - side / 2.f - up;
	glm::vec3 lowerleft = center + side / 2.f - up;

	glm::vec3 normal = glm::normalize(glm::cross(up, side));

	for (int i = 0; i < 3; i++) {

		vertexData[i] = center[i];
		vertexData[i + 3] = left[i];
		vertexData[i + 6] = lowerleft[i];
		vertexData[i + 9] = lowerright[i];
		vertexData[i + 12] = right[i];
		vertexData[i + 15] = upperright[i];
		vertexData[i + 18] = upperleft[i];

	}

	for (int i = 0; i < 21; i += 3) {
		normalData[i] = normal.x;
		normalData[i + 1] = normal.y;
		normalData[i + 2] = normal.z;
		colorData[i] = col.x;
		colorData[i + 1] = col.y;
		colorData[i + 2] = col.z;
	}

	GLushort * indexData = new GLushort[18];
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;

	indexData[3] = 0;
	indexData[4] = 2;
	indexData[5] = 3;

	indexData[6] = 0;
	indexData[7] = 3;
	indexData[8] = 4;

	indexData[9] = 0;
	indexData[10] = 4;
	indexData[11] = 5;

	indexData[12] = 0;
	indexData[13] = 5;
	indexData[14] = 6;

	indexData[15] = 0;
	indexData[16] = 6;
	indexData[17] = 1;

	o.fillBuffers(21, 18, vertexData, normalData, colorData, indexData);

	o.setTriangles(6);

	objects.push_back(o);

}

void World::addCuboid(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec3 col) {

	Object o;
	
	GLfloat * vertexData;
	GLfloat * normalData;
	GLushort * indexData;
	createCuboidData(a, b, c, d, vertexData, normalData, indexData);

	GLfloat * colorData = new GLfloat[72];
	for (int i = 0; i < 72; i += 3) {
		colorData[i] = col[0];
		colorData[i + 1] = col[1];
		colorData[i + 2] = col[2];
	}

	o.fillBuffers(72, 36, vertexData, normalData, colorData, indexData);

	o.setTriangles(12);

	objects.push_back(o);

}

void World::createCuboidData(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, 
						const glm::vec3 &d, GLfloat * &vertexData, GLfloat * &normalData, GLushort * &indexData) {
	
	vertexData = new GLfloat[72];
	normalData = new GLfloat[72];
	indexData = new GLushort[36];

	glm::vec3 e = c + (b - a);
	glm::vec3 f = d + (c - a);
	glm::vec3 g = e + (d - a);
	glm::vec3 h = g + (a - c);
	glm::vec3 n1 = glm::normalize(glm::cross(a - b, c - b));
	glm::vec3 n2 = glm::normalize(glm::cross(d - a, f - a));
	glm::vec3 n3 = glm::normalize(glm::cross(c - e, f - e));

	for (int i = 0; i < 3; i++) {
		
		vertexData[i + 0] = a[i];
		vertexData[i + 3] = b[i];
		vertexData[i + 6] = e[i];
		vertexData[i + 9] = c[i];
		normalData[i + 0] = n1[i];
		normalData[i + 3] = n1[i];
		normalData[i + 6] = n1[i];
		normalData[i + 9] = n1[i];

		vertexData[i + 12] = a[i];
		vertexData[i + 15] = c[i];
		vertexData[i + 18] = f[i];
		vertexData[i + 21] = d[i];
		normalData[i + 12] = n2[i];
		normalData[i + 15] = n2[i];
		normalData[i + 18] = n2[i];
		normalData[i + 21] = n2[i];

		vertexData[i + 24] = c[i];
		vertexData[i + 27] = e[i];
		vertexData[i + 30] = g[i];
		vertexData[i + 33] = f[i];
		normalData[i + 24] = n3[i];
		normalData[i + 27] = n3[i];
		normalData[i + 30] = n3[i];
		normalData[i + 33] = n3[i];

		vertexData[i + 36] = a[i];
		vertexData[i + 39] = d[i];
		vertexData[i + 42] = h[i];
		vertexData[i + 45] = b[i];
		normalData[i + 36] = -n3[i];
		normalData[i + 39] = -n3[i];
		normalData[i + 42] = -n3[i];
		normalData[i + 45] = -n3[i];
		
		vertexData[i + 48] = e[i];
		vertexData[i + 51] = b[i];
		vertexData[i + 54] = h[i];
		vertexData[i + 57] = g[i];
		normalData[i + 48] = -n2[i];
		normalData[i + 51] = -n2[i];
		normalData[i + 54] = -n2[i];
		normalData[i + 57] = -n2[i];

		vertexData[i + 60] = f[i];
		vertexData[i + 63] = g[i];
		vertexData[i + 66] = h[i];
		vertexData[i + 69] = d[i];
		normalData[i + 60] = -n1[i];
		normalData[i + 63] = -n1[i];
		normalData[i + 66] = -n1[i];
		normalData[i + 69] = -n1[i];

	}

	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;
	indexData[3] = 2;
	indexData[4] = 3;
	indexData[5] = 0;

	indexData[6] = 4;
	indexData[7] = 5;
	indexData[8] = 6;
	indexData[9] = 6;
	indexData[10] = 7;
	indexData[11] = 4;

	indexData[12] = 8;
	indexData[13] = 9;
	indexData[14] = 10;
	indexData[15] = 10;
	indexData[16] = 11;
	indexData[17] = 8;

	indexData[18] = 12;
	indexData[19] = 13;
	indexData[20] = 14;
	indexData[21] = 14;
	indexData[22] = 15;
	indexData[23] = 12;

	indexData[24] = 16;
	indexData[25] = 17;
	indexData[26] = 18;
	indexData[27] = 18;
	indexData[28] = 19;
	indexData[29] = 16;

	indexData[30] = 20;
	indexData[31] = 21;
	indexData[32] = 22;
	indexData[33] = 22;
	indexData[34] = 23;
	indexData[35] = 20;

}