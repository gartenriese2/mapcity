#include "Object.hpp"

static unsigned long count = 1;

Object::Object() {

	init();

}

Object::Object(const ObjectType & type, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & col) {

	switch (type) {
		case ObjectType::TRIANGLE:
			init();
			setAsTriangle(a, b, c, col);
			break;
		case ObjectType::QUAD:
			init();
			setAsQuad(a, b, c, col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}
	
}

Object::Object(const ObjectType & type, const glm::vec3 & a, const glm::vec3 & b, const float f, const glm::vec3 & col) {
	
	switch (type) {
		case ObjectType::QUAD:
			init();
			setAsQuad(a,b,f,col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}

}

Object::Object(const ObjectType & type, const glm::vec3 & a, const glm::vec3 & b, const float f1, const float f2, const glm::vec3 & col) {
	
	switch (type) {
		case ObjectType::QUAD:
			init();
			setAsQuad(a,b,f1,f2,col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}
	
}

Object::Object(const ObjectType & type, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & col) {
	
	switch (type) {
		case ObjectType::HEXAGON:
			init();
			setAsHexagon(a,b,col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}
	
}

Object::Object(const ObjectType & type, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d, const glm::vec3 & col) {
	
	switch (type) {
		case ObjectType::CUBOID:
			init();
			setAsCuboid(a,b,c,d,col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}
	
}

Object::Object(const ObjectType & type, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const float f, const glm::vec3 & col) {
	
	switch (type) {
		case ObjectType::CUBOID:
			init();
			setAsCuboid(a,b,c,f,col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}
	
}

Object::Object(const ObjectType & type, const vectorVec3 & v, const float f, const glm::vec3 & col) {
	
	switch (type) {
		case ObjectType::SPLINE:
			init();
			setAsSpline(v,f,col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}
	
}

Object::Object(const ObjectType & type, const vectorVec3 & v, const glm::vec3 & center, const glm::vec3 & col) {
	
	switch (type) {
		case ObjectType::POLYGON:
			init();
			setAsPolygon(v,center,col);
			break;
		default:
			std::cout << "no such constructor!\n";
	}
	
}

Object::~Object() {

	// glDeleteVertexArrays(1, &m_vertexArray);

	// glDeleteBuffers(1, &m_vertexBuffer);
	// glDeleteBuffers(1, &m_normalBuffer);
	// glDeleteBuffers(1, &m_colorBuffer);
	// glDeleteBuffers(1, &m_indexBuffer);

}

void Object::init() {

	m_ID = count++;

	glGenVertexArrays(1, &m_vertexArray);

	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_normalBuffer);
	glGenBuffers(1, &m_colorBuffer);
	glGenBuffers(1, &m_indexBuffer);

	m_triangles = 0;
	m_modelMatrix = glm::mat4(1.f);

}

void Object::fillBuffers(const int size, const int indices, GLfloat * &vertexData, 
					GLfloat * &normalData, GLfloat * &colorData, GLushort * &indexData) {

	glBindVertexArray(m_vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, normalData, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * size, colorData, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
 	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices, indexData, GL_STATIC_DRAW);

}

void Object::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 3 * m_triangles, GL_UNSIGNED_SHORT, (void*)0);

}

/**
 * adds a triangle to the object vector
 * @param a   first point
 * @param b   second point (anticlockwise)
 * @param c   third point (anticlockwise)
 * @param col optional color
 */
void Object::setAsTriangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & col) {

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

	fillBuffers(9, 3, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(1);
	
}

/**
 * adds a quad to the object vector
 * @param a   first point
 * @param b   second point (anticlockwise)
 * @param d   fourth point (anticlockwise)
 * @param col optional color
 */
void Object::setAsQuad(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & d, const glm::vec3 & col) {

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

	fillBuffers(12, 6, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(2);

}

/**
 * adds a quad to the object vector
 * @param start midpoint of the left side
 * @param end   midpoint of the right side
 * @param width length of left/right side
 * @param col   optional color
 */
void Object::setAsQuad(const glm::vec3 & start, const glm::vec3 & end, const float width, const glm::vec3 & col) {

	glm::vec3 l = end - start;
	glm::vec3 a = start + glm::normalize(glm::vec3(l.z, 0, -l.x)) * width / 2.f;
	glm::vec3 b = start + glm::normalize(glm::vec3(-l.z, 0, l.x)) * width / 2.f;
	glm::vec3 c = end + glm::normalize(glm::vec3(-l.z, 0, l.x)) * width / 2.f;
	glm::vec3 d = end + glm::normalize(glm::vec3(l.z, 0, -l.x)) * width / 2.f;

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

	fillBuffers(12, 6, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(2);

}

/**
 * adds a quad to the object vector
 * @param start      midpoint of left side
 * @param end        midpoint of right side
 * @param widthStart length of left side
 * @param widthEnd   length of right side
 * @param col        optional color
 */
void Object::setAsQuad(const glm::vec3 & start, const glm::vec3 & end, const float widthStart, const float widthEnd, const glm::vec3 & col) {

	glm::vec3 l = end - start;
	glm::vec3 a = start + glm::normalize(glm::vec3(l.z, 0, -l.x)) * widthStart / 2.f;
	glm::vec3 b = start + glm::normalize(glm::vec3(-l.z, 0, l.x)) * widthStart / 2.f;
	glm::vec3 c = end + glm::normalize(glm::vec3(-l.z, 0, l.x)) * widthEnd / 2.f;
	glm::vec3 d = end + glm::normalize(glm::vec3(l.z, 0, -l.x)) * widthEnd / 2.f;

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

	fillBuffers(12, 6, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(2);

}

/**
 * adds a hexagon to the object vector
 * @param center center of the hexagon
 * @param left   left point of the hexagon
 * @param col    optional color
 */
void Object::setAsHexagon(const glm::vec3 & center, const glm::vec3 & left, const glm::vec3 & col) {

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

	fillBuffers(21, 18, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(6);

}

/**
 * adds a cuboid to the object vector
 * @param a   [description]
 * @param b   [description]
 * @param c   [description]
 * @param d   [description]
 * @param col [description]
 */
void Object::setAsCuboid(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d, const glm::vec3 & col) {
	
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

	fillBuffers(72, 36, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(12);

}

void Object::setAsCuboid(const glm::vec3 & center, const glm::vec3 & dirX, const glm::vec3 & dirZ, const float height, const glm::vec3 & col) {

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

	fillBuffers(72, 36, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(12);

}

void Object::createCuboidData(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, 
						const glm::vec3 & d, GLfloat * & vertexData, GLfloat * & normalData, GLushort * & indexData) {
	
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

void Object::setAsSpline(const vectorVec3 & pts, const float width, const glm::vec3 & col) {

	assert(pts.size() > 1);

	std::vector<GLfloat> vertexData;
	std::vector<GLfloat> normalData;
	std::vector<GLushort> indexData;
	std::vector<GLfloat> colorData;

	float smoothness = 100.f;

	for (int i = 0; i < pts.size() - 1; i++) {
		
		glm::vec3 old = pts[i];
		glm::vec3 tmp, tmp2, mA, mB;

		if (i == 0) mA = glm::normalize(pts[i+1] - pts[i]);
		else mA = glm::normalize(pts[i+1] - pts[i-1]);
		if (i + 2 == pts.size()) mB = glm::normalize(pts[i+1] - pts[i]);
		else mB = glm::normalize(pts[i+2] - pts[i]);

		float stretch = (2.f - glm::pow(glm::dot(mA, mB), 2.f)) * width / 10.0;

		float step = 1.f / glm::sqrt(glm::pow(pts[i+1].x - pts[i].x, 2.f) + glm::pow(pts[i + 1].z - pts[i].z, 2.f));

		for (float t = 0.f; t < 1.f; t += step) {

			tmp = drawHermite(pts[i] / smoothness, pts[i+1] / smoothness, mA, mB, t) * smoothness;
			tmp.y = pts[i].y + (pts[i + 1].y - pts[i].y) * t;
			glm::vec3 tmp2 = old + (tmp - old) * stretch;

			addQuadToData(vertexData, normalData, indexData, colorData, old, tmp2, width, col);

			old = tmp;

		}

		addQuadToData(vertexData, normalData, indexData, colorData, old, pts[i + 1], width, col);

	}

	GLfloat * vertices = &vertexData[0];
	GLfloat * normals = &normalData[0];
	GLushort * indices = &indexData[0];
	GLfloat * colors = &colorData[0];

	fillBuffers(vertexData.size(), indexData.size(), vertices, normals, colors, indices);
	
	setTriangles(indexData.size() / 3);
	
}

glm::vec3 Object::drawHermite(const glm::vec3 & A, const glm::vec3 & B, const glm::vec3 & mA, const glm::vec3 & mB, const float t) {

	float t3 = glm::pow(t, 3.f);
	float t2 = glm::pow(t, 2.f);

	return (2*t3 - 3*t2 + 1) * A + (t3 - 2*t2 + t) * mA + (3*t2 - 2*t3) * B + (t3 - t2) * mB;

}

void Object::addQuadToData(	std::vector<GLfloat> & vertexData,
							std::vector<GLfloat> & normalData,
							std::vector<GLushort> & indexData,
							std::vector<GLfloat> & colorData,
							const glm::vec3 & start,
							const glm::vec3 & end,
							const float width,
							const glm::vec3 & color) {

	glm::vec3 l = end - start;
	glm::vec3 a = start + glm::normalize(glm::vec3(l.z, 0, -l.x)) * width / 2.f;
	glm::vec3 b = start + glm::normalize(glm::vec3(-l.z, 0, l.x)) * width / 2.f;
	glm::vec3 c = end + glm::normalize(glm::vec3(-l.z, 0, l.x)) * width / 2.f;
	glm::vec3 d = end + glm::normalize(glm::vec3(l.z, 0, -l.x)) * width / 2.f;

	int len = vertexData.size() / 3;

	vertexData.push_back(a[0]);
	vertexData.push_back(a[1]);
	vertexData.push_back(a[2]);

	vertexData.push_back(b[0]);
	vertexData.push_back(b[1]);
	vertexData.push_back(b[2]);

	vertexData.push_back(c[0]);
	vertexData.push_back(c[1]);
	vertexData.push_back(c[2]);

	vertexData.push_back(d[0]);
	vertexData.push_back(d[1]);
	vertexData.push_back(d[2]);

	glm::vec3 n = glm::normalize(glm::cross(c - b, a - b));
	for (int i = 0; i < 4; i++) {
		normalData.push_back(n[0]);
		normalData.push_back(n[1]);
		normalData.push_back(n[2]);
	}

	for (int i = 0; i < 4; i++) {
		colorData.push_back(color[0]);
		colorData.push_back(color[1]);
		colorData.push_back(color[2]);
	}

	indexData.push_back(len);
	indexData.push_back(len + 1);
	indexData.push_back(len + 2);
	indexData.push_back(len + 2);
	indexData.push_back(len + 3);
	indexData.push_back(len);

}

void Object::setAsPolygon(const vectorVec3 & pts, const glm::vec3 & center, const glm::vec3 & col) {

	assert(pts.size() > 2);

	int numTriangles = pts.size();
	int numVertices = pts.size() + 1;

	GLfloat * vertexData = new GLfloat[numVertices * 3];
	GLfloat * normalData = new GLfloat[numVertices * 3];
	GLfloat * colorData = new GLfloat[numVertices * 3];

	glm::vec3 normal = -glm::normalize(glm::cross(pts[0] - center, pts[1] - center));

	vertexData[0] = center[0];
	vertexData[1] = center[1];
	vertexData[2] = center[2];
	normalData[0] = normal.x;
	normalData[1] = normal.y;
	normalData[2] = normal.z;
	colorData[0] = col.x;
	colorData[1] = col.y;
	colorData[2] = col.z;

	for (int i = 3; i < numVertices * 3; i += 3) {

		vertexData[i] = pts[(i / 3) - 1][0];
		vertexData[i + 1] = pts[(i / 3) - 1][1];
		vertexData[i + 2] = pts[(i / 3) - 1][2];
		normalData[i] = normal.x;
		normalData[i + 1] = normal.y;
		normalData[i + 2] = normal.z;
		colorData[i] = col.x;
		colorData[i + 1] = col.y;
		colorData[i + 2] = col.z;

	}

	GLushort * indexData = new GLushort[numTriangles * 3];
	int count = 0;
	for (int i = 0; i < numTriangles * 3; i += 3)	{
		indexData[i] = 0;
		if (count + 2 > numTriangles) {
			indexData[i + 1] = 1;
		} else {
			indexData[i + 1] = count + 2;
		}
		indexData[i + 2] = count + 1;
		count++;
	}

	fillBuffers(numVertices * 3, numTriangles * 3, vertexData, normalData, colorData, indexData);
	delete vertexData;
	delete normalData;
	delete colorData;
	delete indexData;

	setTriangles(numTriangles);

}