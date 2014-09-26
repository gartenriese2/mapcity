#include "sphere.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_minRings = 2;
static constexpr unsigned int k_maxRings = 1000;
static constexpr unsigned int k_minSectors = 3;
static constexpr unsigned int k_maxSectors = 1000;

Sphere::Sphere(const glm::vec3 & center, float radius, unsigned int rings,
	unsigned int sectors, const glm::vec3 & color) {

	rings = rings < k_minRings ? k_minRings : rings > k_maxRings ? k_maxRings : rings;
	sectors = sectors < k_minSectors ? k_minSectors : sectors > k_maxSectors ? k_maxSectors : sectors;

	init(center, radius, rings, sectors, getColorVector(color, (rings - 1) * sectors + 2));

}

Sphere::Sphere(const glm::vec3 & center, float radius, unsigned int rings,
	unsigned int sectors, const std::initializer_list<glm::vec3> & colors) {

	rings = rings < k_minRings ? k_minRings : rings > k_maxRings ? k_maxRings : rings;
	sectors = sectors < k_minSectors ? k_minSectors : sectors > k_maxSectors ? k_maxSectors : sectors;

	init(center, radius, rings, sectors, getColorVector(colors, (rings - 1) * sectors + 2));

}

std::shared_ptr<Object> Sphere::getCopy() {

	return std::shared_ptr<Object>(new Sphere(*this));

}

std::shared_ptr<Object> Sphere::getInstance() const {

	static std::shared_ptr<Object> ptr(new Sphere({0.f, 0.f, 0.f}, 0.5f, 50, 50,
		{1.f, 1.f, 1.f}));
	
	std::shared_ptr<Object> instance(new Sphere());
	instance->makeInstance(*ptr);
	return instance;

}

void Sphere::init(const glm::vec3 & center, float radius, unsigned int rings,
	unsigned int sectors, const std::vector<GLfloat> & colors) {

	Object::init();

	setCenter({0.f, 0.f, 0.f});

	std::vector<GLfloat> vertices {0.f, radius, 0.f};
	std::vector<GLfloat> normals {0.f, 1.f, 0.f};
	
	for(unsigned int r = 1; r < rings; ++r) {
		
		float y = glm::cos(static_cast<float>(r) / static_cast<float>(rings) * glm::pi<float>());

		for(unsigned int s = 0; s < sectors; ++s) {
			
			float x = -glm::sin(static_cast<float>(s) / static_cast<float>(sectors) * 2.f * glm::pi<float>());
			x *= glm::sin(static_cast<float>(r) / static_cast<float>(rings) * glm::pi<float>());
			float z = glm::cos(static_cast<float>(s) / static_cast<float>(sectors) * 2.f * glm::pi<float>());
			z *= glm::sin(static_cast<float>(r) / static_cast<float>(rings) * glm::pi<float>());

			vertices.emplace_back(radius * x);
			vertices.emplace_back(radius * y);
			vertices.emplace_back(radius * z);

			normals.emplace_back(x);
			normals.emplace_back(y);
			normals.emplace_back(z);

		}

	}

	vertices.emplace_back(0.f);
	vertices.emplace_back(-radius);
	vertices.emplace_back(0.f);
	normals.emplace_back(0.f);
	normals.emplace_back(-1.f);
	normals.emplace_back(0.f);

	std::vector<GLushort> indices;

	for(unsigned int s = 0; s < sectors; s++) {

		indices.emplace_back(0);
		indices.emplace_back((s + 1) % sectors + 1);
		indices.emplace_back(s + 1);

	}

	for(unsigned int r = 0; r < rings - 1; r++) {
		for(unsigned int s = 0; s < sectors; s++) {

			indices.emplace_back(r * sectors + s + 1);
			indices.emplace_back(r * sectors + (s + 1) % sectors + 1);
			indices.emplace_back((r + 1) * sectors + (s + 1) % sectors + 1);

			indices.emplace_back(r * sectors + s + 1);
			indices.emplace_back((r + 1) * sectors + (s + 1) % sectors + 1);
			indices.emplace_back((r + 1) * sectors + s + 1);

		}
	}

	unsigned int start = static_cast<unsigned int>(vertices.size()) / 3 - 1 - sectors;
	for(unsigned int s = 0; s < sectors; s++) {

		indices.emplace_back(start + s);
		indices.emplace_back(start + (s + 1) % sectors);
		indices.emplace_back(start + sectors);

	}

	m_vertexBufferPtr->insertData(vertices);

	m_colorBufferPtr->insertData(colors);

	m_normalBufferPtr->insertData(normals);

	m_indexBufferPtr->insertData(indices);

	moveTo(center);

	m_data.insert(m_data.begin(), {glm::vec4(center, 0.f), glm::vec4(radius), glm::vec4(rings), glm::vec4(sectors)});

	fillTriangles(indices, vertices);

}

void Sphere::draw() const {

	m_vaoPtr->draw(static_cast<GLsizei>(m_indexBufferPtr->getSize()));

}
