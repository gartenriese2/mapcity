#include "cone.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_minSections = 3;
static constexpr unsigned int k_maxSections = 1000;

Cone::Cone(const glm::vec3 & base, const glm::vec3 & axis, float length, float lowerRadius,
	float upperRadius, unsigned int sections, const glm::vec3 & color) {

	sections = sections < k_minSections ? k_minSections : sections > k_maxSections ? k_maxSections : sections;

	if (length > 0.f && (lowerRadius > 0.f || upperRadius > 0.f) && glm::length(axis) > 0.f) {

		if (lowerRadius > 0.f && upperRadius > 0.f) {
			init(base, axis, length, lowerRadius, upperRadius, sections, getColorVector(color, 4 * sections + 2));
		} else {
			init(base, axis, length, lowerRadius, upperRadius, sections, getColorVector(color, 3 * sections + 1));
		}

	}

}

Cone::Cone(const glm::vec3 & base, const glm::vec3 & axis, float length, float lowerRadius,
	float upperRadius, unsigned int sections, const std::initializer_list<glm::vec3> & colors) {

	sections = sections < k_minSections ? k_minSections : sections > k_maxSections ? k_maxSections : sections;

	if (length > 0.f && (lowerRadius > 0.f || upperRadius > 0.f) && glm::length(axis) > 0.f) {

		if (lowerRadius > 0.f && upperRadius > 0.f) {
			init(base, axis, length, lowerRadius, upperRadius, sections, getColorVector(colors, 4 * sections + 2));
		} else {
			init(base, axis, length, lowerRadius, upperRadius, sections, getColorVector(colors, 3 * sections + 1));
		}

	}

}

std::shared_ptr<Object> Cone::getCopy() {

	return std::shared_ptr<Object>(new Cone(*this));

}

std::shared_ptr<Object> Cone::getInstance() const {

	static std::shared_ptr<Object> ptr(new Cone({0.f, -0.5f, 0.f}, {0.f, 1.f, 0.f},
		1.f, 0.5f, 0.5f, 50, {1.f, 1.f, 1.f}));
	
	std::shared_ptr<Object> instance(new Cone());
	instance->makeInstance(*ptr);
	return instance;

}

void Cone::init(const glm::vec3 & base, const glm::vec3 & axis, float length, float lowerRadius,
	float upperRadius, unsigned int sections, const std::vector<GLfloat> & colors) {

	Object::init();

	setCenter({0.f, 0.f, 0.f});

	float lowerZ = -length / 2.f;
	float upperZ = length / 2.f;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	if (lowerRadius > 0.f) {

		// center of lower circle
		vertices.emplace_back(0.f);
		vertices.emplace_back(0.f);
		vertices.emplace_back(lowerZ);
		normals.emplace_back(0.f);
		normals.emplace_back(0.f);
		normals.emplace_back(-1.f);

		// lower circle flat
		for (unsigned int i = 0; i < sections; ++i) {
			
			vertices.emplace_back(glm::cos(i * 2*glm::pi<float>() / sections) * lowerRadius);
			vertices.emplace_back(glm::sin(i * 2*glm::pi<float>() / sections) * lowerRadius);
			vertices.emplace_back(lowerZ);
			normals.emplace_back(0.f);
			normals.emplace_back(0.f);
			normals.emplace_back(-1.f);

		}

		// lower circle sides
		for (unsigned int i = 0; i < sections; ++i) {
			
			vertices.emplace_back(glm::cos(i * 2*glm::pi<float>() / sections) * lowerRadius);
			vertices.emplace_back(glm::sin(i * 2*glm::pi<float>() / sections) * lowerRadius);
			vertices.emplace_back(lowerZ);
			glm::vec3 n = {glm::cos(i * 2*glm::pi<float>() / sections) * lowerRadius,
						glm::sin(i * 2*glm::pi<float>() / sections) * lowerRadius,
						(lowerRadius - upperRadius) * (lowerRadius - upperRadius) / length};
			glm::normalize(n);
			normals.emplace_back(n[0]);
			normals.emplace_back(n[1]);
			normals.emplace_back(lowerRadius > upperRadius ? n[2] : -n[2]);

		}

	} else {

		for (unsigned int i = 0; i < sections; ++i) {
			vertices.emplace_back(0.f);
			vertices.emplace_back(0.f);
			vertices.emplace_back(lowerZ);
			glm::vec3 n = {glm::cos(i * 2*glm::pi<float>() / sections) * lowerRadius,
						glm::sin(i * 2*glm::pi<float>() / sections) * lowerRadius,
						(lowerRadius - upperRadius) * (lowerRadius - upperRadius) / length};
			glm::normalize(n);
			normals.emplace_back(n[0]);
			normals.emplace_back(n[1]);
			normals.emplace_back(lowerRadius > upperRadius ? n[2] : -n[2]);
		}

	}

	if (upperRadius > 0.f) {

		// upper circle sides
		for (unsigned int i = 0; i < sections; ++i) {
			
			vertices.emplace_back(glm::cos(i * 2*glm::pi<float>() / sections) * upperRadius);
			vertices.emplace_back(glm::sin(i * 2*glm::pi<float>() / sections) * upperRadius);
			vertices.emplace_back(upperZ);
			glm::vec3 n = {glm::cos(i * 2*glm::pi<float>() / sections) * upperRadius,
						glm::sin(i * 2*glm::pi<float>() / sections) * upperRadius,
						(lowerRadius - upperRadius) * (lowerRadius - upperRadius) / length};
			glm::normalize(n);
			normals.emplace_back(n[0]);
			normals.emplace_back(n[1]);
			normals.emplace_back(lowerRadius > upperRadius ? n[2] : -n[2]);

		}

		// upper circle flat
		for (unsigned int i = 0; i < sections; ++i) {
			
			vertices.emplace_back(glm::cos(i * 2*glm::pi<float>() / sections) * upperRadius);
			vertices.emplace_back(glm::sin(i * 2*glm::pi<float>() / sections) * upperRadius);
			vertices.emplace_back(upperZ);
			normals.emplace_back(0.f);
			normals.emplace_back(0.f);
			normals.emplace_back(1.f);

		}

		// center of upper circle
		vertices.emplace_back(0.f);
		vertices.emplace_back(0.f);
		vertices.emplace_back(upperZ);
		normals.emplace_back(0.f);
		normals.emplace_back(0.f);
		normals.emplace_back(1.f);

	} else {

		for (unsigned int i = 0; i < sections; ++i) {
			vertices.emplace_back(0.f);
			vertices.emplace_back(0.f);
			vertices.emplace_back(upperZ);
			glm::vec3 n = {glm::cos(i * 2*glm::pi<float>() / sections) * upperRadius,
						glm::sin(i * 2*glm::pi<float>() / sections) * upperRadius,
						(lowerRadius - upperRadius) * (lowerRadius - upperRadius) / length};
			glm::normalize(n);
			normals.emplace_back(n[0]);
			normals.emplace_back(n[1]);
			normals.emplace_back(lowerRadius > upperRadius ? n[2] : -n[2]);
		}

	}

	if (axis != glm::vec3(0.f, 0.f, -1.f)) {
		// rotating vertices and normals
		glm::mat4 rotationMatrix;
		if (axis == glm::vec3(0.f, 0.f, 1.f)) {
			rotationMatrix = glm::rotate(glm::mat4(1.f), glm::pi<float>(), {0.f, 1.f, 0.f});
		} else {
			rotationMatrix = glm::rotate(glm::mat4(1.f),
				glm::acos(glm::dot(axis, {0.f, 0.f, 1.f}) / glm::length(axis)),
				glm::cross(-axis, {0.f, 0.f, 1.f}));
		}
		for (unsigned int i = 0; i < vertices.size(); i += 3) {
			glm::vec4 rotVert = rotationMatrix * glm::vec4(vertices[i], vertices[i + 1], vertices[i + 2], 1.f);
			vertices[i] = rotVert.x;
			vertices[i + 1] = rotVert.y;
			vertices[i + 2] = rotVert.z;

			glm::vec4 rotNorm = rotationMatrix * glm::vec4(normals[i], normals[i + 1], normals[i + 2], 1.f);
			normals[i] = rotNorm.x;
			normals[i + 1] = rotNorm.y;
			normals[i + 2] = rotNorm.z;
		}
	}

	m_vertexBufferPtr->insertData(vertices);

	m_colorBufferPtr->insertData(colors);

	m_normalBufferPtr->insertData(normals);

	std::vector<GLushort> indices;
	if (lowerRadius > 0.f) {
		
		for (unsigned int i = 1; i < sections + 1; ++i) {
			indices.emplace_back(0);
			indices.emplace_back((i == sections) ? 1 : (i + 1));
			indices.emplace_back(i);
		}

		if (upperRadius > 0.f) {
			
			for (unsigned int i = sections + 1; i < 2 * sections + 1; ++i) {
				indices.emplace_back(i);
				indices.emplace_back((i == 2 * sections) ? (sections + 1) : (i + 1));
				indices.emplace_back(i + sections);

				indices.emplace_back(i + sections);
				indices.emplace_back((i == 2 * sections) ? (sections + 1) : (i + 1));
				indices.emplace_back((i == 2 * sections) ? (2 * sections + 1) : (i + sections + 1));
			}

			for (unsigned int i = 3 * sections + 1; i < 4 * sections + 1; ++i) {
				indices.emplace_back(4 * sections + 1);
				indices.emplace_back((i == 4 * sections) ? (3 * sections + 1) : (i + 1));
				indices.emplace_back(i);
			}

		} else {

			for (unsigned int i = sections + 1; i < 2 * sections + 1; ++i) {
				indices.emplace_back(i);
				indices.emplace_back((i == 2 * sections) ? (sections + 1) : (i + 1));
				indices.emplace_back(i + sections);
			}

		}

	} else {

		for (unsigned int i = 0; i < sections; ++i) {
			indices.emplace_back(i);
			indices.emplace_back((i == sections - 1) ? sections : (sections + i + 1));
			indices.emplace_back(sections + i);
		}

		for (unsigned int i = 2 * sections; i < 3 * sections; ++i) {
			indices.emplace_back(i);
			indices.emplace_back((i == 3 * sections - 1) ? (2 * sections) : (i + 1));
			indices.emplace_back(3 * sections);
		}

	}


	m_indexBufferPtr->insertData(indices);

	moveTo(base + glm::normalize(axis) * length / 2.f);

	m_data.insert(m_data.begin(), {glm::vec4(base, 0.f), glm::vec4(axis, 0.f),
		glm::vec4(length, lowerRadius, upperRadius, 0.f), glm::vec4(sections)});

	fillTriangles(indices, vertices);

}

void Cone::draw() const {

	m_vaoPtr->draw(static_cast<GLsizei>(m_indexBufferPtr->getSize()));

}
