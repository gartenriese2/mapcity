#include "triangle.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_vertices = 3;

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & color) {

	init(a, b, c, getColorVector(color, k_vertices));

}

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const std::initializer_list<glm::vec3> & colors) {

	init(a, b, c, getColorVector(colors, k_vertices));

}

std::shared_ptr<Object> Triangle::getCopy() {

	return std::shared_ptr<Object>(new Triangle(*this));

}

std::shared_ptr<Object> Triangle::getInstance() const {

	static std::shared_ptr<Object> ptr(new Triangle({-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f},
		{0.f, 0.5f, 0.f}, {1.f, 1.f, 1.f}));
	
	std::shared_ptr<Object> instance(new Triangle());
	instance->makeInstance(*ptr);
	return instance;

}

void Triangle::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const std::vector<GLfloat> & colors) {

	Object::init();

	setCenter((a + b + c) / 3.f);

	m_vertexBufferPtr->insertData({
		a.x, a.y, a.z,
		b.x, b.y, b.z,
		c.x, c.y, c.z
	});

	m_colorBufferPtr->insertData(colors);

	glm::vec3 normal = glm::cross(b - a, c - a);
	m_normalBufferPtr->insertData({
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z
	});

	m_indexBufferPtr->insertData({
		0, 1, 2
	});

	m_data.insert(m_data.begin(), {glm::vec4(a, 0.f), glm::vec4(b, 0.f), glm::vec4(c, 0.f), glm::vec4(0.f)});

	m_triangles.emplace_back(glm::vec4(a.x, a.y, a.z, 1.f), glm::vec4(b.x, b.y, b.z, 1.f), glm::vec4(c.x, c.y, c.z, 1.f));

}

void Triangle::draw() const {

	m_vaoPtr->draw(static_cast<GLsizei>(m_indexBufferPtr->getSize()));

}
