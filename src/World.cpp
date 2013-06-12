#include "World.hpp"

long counter  = 0;

World::World(const int height, const int width) {
	createMap(height, width);
}

void World::createMap(const int height, const int width) {
	m_map = new Map(height, width);

	std::vector<Hexagon> v = m_map->getHexaVector();
	for (auto h : v) {
		addHexagon(h.getCenter(), h.getLeft());
	}
}

void World::addTriangle(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 col) {
	
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

	GLushort * indexData = new GLushort[3];
	indexData[0] = 0;
	indexData[1] = 1;
	indexData[2] = 2;

	o.fillBuffers(9, 3, vertexData, normalData, colorData, indexData);

	o.setTriangles(1);

	m_objects.push_back(o);
	
}

void World::addQuad(const glm::vec3 a, const glm::vec3 b, const glm::vec3 d, const glm::vec3 col) {

	Object o;

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

	m_objects.push_back(o);

}

void World::addQuad(const glm::vec3 start, const glm::vec3 end, const float width, const glm::vec3 col) {

	Object o;

	glm::vec3 l = end - start;
	glm::vec3 a = start + glm::normalize(glm::vec3(l.z, start.y, -l.x)) * width / 2.f;
	glm::vec3 b = start + glm::normalize(glm::vec3(-l.z, start.y, l.x)) * width / 2.f;
	glm::vec3 c = end + glm::normalize(glm::vec3(-l.z, end.y, l.x)) * width / 2.f;
	glm::vec3 d = end + glm::normalize(glm::vec3(l.z, end.y, -l.x)) * width / 2.f;

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

	m_objects.push_back(o);

}

void World::addHexagon(const glm::vec3 center, const glm::vec3 left, const glm::vec3 col) {

	Object o;

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

	m_objects.push_back(o);

}

void World::addCuboid(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d, const glm::vec3 col) {

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

	m_objects.push_back(o);

}

void World::addCuboid(const glm::vec3 center, const glm::vec3 dirX, const glm::vec3 dirZ, const float height, const glm::vec3 col) {

	Object o;

	GLfloat * vertexData;
	GLfloat * normalData;
	GLushort * indexData;

	glm::vec3 a = center + dirX + dirZ;
	glm::vec3 b = center + dirX - dirZ;
	glm::vec3 c = a + glm::vec3(0,1,0) * height;
	glm::vec3 d = center - dirX + dirZ;

	createCuboidData(a, b, c, d, vertexData, normalData, indexData);

	GLfloat * colorData = new GLfloat[72];
	for (int i = 0; i < 72; i += 3) {
		colorData[i] = col[0];
		colorData[i + 1] = col[1];
		colorData[i + 2] = col[2];
	}

	o.fillBuffers(72, 36, vertexData, normalData, colorData, indexData);

	o.setTriangles(12);

	m_objects.push_back(o);

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

void World::addSpline(std::vector<glm::vec3> pts, const float width, const glm::vec3 col) {

	assert(pts.size() > 2);

	if (pts.size() % 2 == 1) {
		glm::vec3 tmp = pts[pts.size() - 1];
		pts.pop_back();
		pts.push_back(pts[pts.size() - 2] + (tmp - pts[pts.size() - 2]) * 0.5f);
		pts.push_back(tmp);
	}

	for (int i = 3; i < pts.size(); i += 2) {

		float len = glm::sqrt(glm::pow(pts[i].x - pts[i - 3].x, 2.f) 
			+ glm::pow(pts[i].y - pts[i - 3].y, 2.f) + glm::pow(pts[i].z - pts[i - 3].z, 2.f));
		float step = 1.f / len;
		std::cout << step << "\n";
		glm::vec3 old = pts[i - 3];
		glm::vec3 tmp;
		for (float t = 0.f; t < 1.f; t += step) {
			tmp = drawBezier(pts[i - 3], pts[i - 2], pts[i - 1], pts[i], t);
			glm::vec3 x = old + (tmp - old) * 1.1f;
			addQuad(old, x, width, col);
			old = tmp;
		}
		addQuad(tmp, pts[i], width, col);

	}
	
}

glm::vec3 World::drawBezier(glm::vec3 A, glm::vec3 B, glm::vec3 C, glm::vec3 D, float t) {
    glm::vec3 P;

    P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 -t), 2) * B.x + 3 * (1-t) * pow(t, 2)* C.x + pow (t, 3)* D.x;
    P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 -t), 2) * B.y + 3 * (1-t) * pow(t, 2)* C.y + pow (t, 3)* D.y;
    P.z = pow((1 - t), 3) * A.z + 3 * t * pow((1 -t), 2) * B.z + 3 * (1-t) * pow(t, 2)* C.z + pow (t, 3)* D.z;
	// float t3 = glm::pow(t, 3.f);
	// float t2 = glm::pow(t, 2.f);
 //    return 0.5f * ((2.f * B) + (-A + C) * t + (2.f*A - 5.f*B + 4.f*C - D) * t2 + (-A + 3.f*B- 3.f*C + D) * t3);

    return P;
}

// glm::vec3 World::drawHermite(glm::vec3 A, glm::vec3 B, float mA, float mB, float t) {

// 	float t3 = glm::pow(t, 3.f);
// 	float t2 = glm::pow(t, 2.f);

// 	return (2*t3 - 3*t2 + 1) * A + 

// }