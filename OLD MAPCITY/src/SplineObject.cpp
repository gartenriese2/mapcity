#include "SplineObject.hpp"

SplineObject::SplineObject(const vectorVec3 & path, const float width, const glm::vec3 & color) {

	m_path = path;
	m_width = width;
	m_color = color;

	initObject();

}

SplineObject::~SplineObject() {

}

void SplineObject::initObject() {

	assert(m_path.size() > 1);

	std::vector<GLfloat> vertexData;
	std::vector<GLfloat> normalData;
	std::vector<GLushort> indexData;
	std::vector<GLfloat> colorData;

	float smoothness, step;

	for (unsigned long i = 0; i < m_path.size() - 1; i++) {
		
		glm::vec3 mA, mB;

		if (i == 0) 				mA = glm::normalize(m_path[i+1] - m_path[i]);
		else 						mA = glm::normalize(m_path[i+1] - m_path[i-1]);
		if (i + 2 == m_path.size()) 	mB = glm::normalize(m_path[i+1] - m_path[i]);
		else 						mB = glm::normalize(m_path[i+2] - m_path[i]);

		smoothness = glm::sqrt(glm::pow(m_path[i+1].x - m_path[i].x, 2.f) + glm::pow(m_path[i + 1].z - m_path[i].z, 2.f));
		
		step = 1.f / smoothness * 0.5f;
		if (step >= 0.5f) step = 0.499f;

		glm::vec3 tangentA, tangentB, normalA, normalB, waybefore, before, middle, next;
		vectorVec3 polygon;
		before = m_path[i];
		waybefore = m_path[i];

		for (float t = step; t < 1.f; t += step) {

			if (t == step) {
				middle = drawHermite(m_path[i] / smoothness, m_path[i+1] / smoothness, mA, mB, t) * smoothness;
			}

			if (t + step < 1.f) {
				next = drawHermite(m_path[i] / smoothness, m_path[i+1] / smoothness, mA, mB, t + step) * smoothness;
			} else {
				next = m_path[i+1];
			}

			if (t == step) {
				tangentA = mA;
			} else {
				tangentA = middle - waybefore;
			}
			tangentA.y = 0.f;
			normalA = glm::normalize(glm::cross(glm::vec3(0,1,0),tangentA));

			tangentB = next - before;
			tangentB.y = 0.f;
			normalB = glm::normalize(glm::cross(glm::vec3(0,1,0),tangentB));

			polygon.push_back(before + normalA * (m_width / 2.f));
			polygon.push_back(middle + normalB * (m_width / 2.f));
			polygon.push_back(middle - normalB * (m_width / 2.f));
			polygon.push_back(before - normalA * (m_width / 2.f));

			addQuadToData(vertexData, normalData, indexData, colorData, polygon, m_color);

			waybefore = before;
			before = middle;
			middle = next;
			polygon.clear();

		}

		normalA = glm::normalize(glm::cross(glm::vec3(0,1,0), tangentB));
		normalB = glm::normalize(glm::cross(glm::vec3(0,1,0), mB));

		polygon.push_back(before + normalA * (m_width / 2.f));
		polygon.push_back(middle + normalB * (m_width / 2.f));
		polygon.push_back(middle - normalB * (m_width / 2.f));
		polygon.push_back(before - normalA * (m_width / 2.f));

		addQuadToData(vertexData, normalData, indexData, colorData, polygon, m_color);

		polygon.clear();

	}

	GLfloat * vertices = &vertexData[0];
	GLfloat * normals = &normalData[0];
	GLushort * indices = &indexData[0];
	GLfloat * colors = &colorData[0];

	fillBuffers(vertexData.size(), indexData.size(), vertices, normals, colors, indices);
	
	setTriangles(static_cast<int>(indexData.size()) / 3);

}