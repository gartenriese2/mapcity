#include "quadrilateral.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_vertices = 4;

Quadrilateral::Quadrilateral(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d,
	const glm::vec3 & color) {

	init(a, b, c, d, getColorVector(color, k_vertices));

}

Quadrilateral::Quadrilateral(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d,
	const std::initializer_list<glm::vec3> & colors) {

	init(a, b, c, d, getColorVector(colors, k_vertices));

}

std::shared_ptr<Object> Quadrilateral::getCopy() {

	return std::shared_ptr<Object>(new Quadrilateral(*this));

}

std::shared_ptr<Object> Quadrilateral::getInstance() const {

	static std::shared_ptr<Object> ptr(new Quadrilateral({-1.f, -1.f, 0.f}, {1.f, -1.f, 0.f},
		{1.f, 1.f, 0.f}, {-1.f, 1.f, 0.f}, {1.f, 1.f, 1.f}));
	
	std::shared_ptr<Object> instance(new Quadrilateral());
	instance->makeInstance(*ptr);
	return instance;

}

void Quadrilateral::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d,
	const std::vector<GLfloat> & colors) {

	Object::init();

	setCenter((a + b + c + d) / 4.f);

	m_vertexBufferPtr->insertData({
		a.x, a.y, a.z,
	   	b.x, b.y, b.z,
	   	c.x, c.y, c.z,
	   	d.x, d.y, d.z
	});

	m_colorBufferPtr->insertData(colors);

	glm::vec3 nA = glm::cross(b - a, d - a);
	glm::vec3 nB = glm::cross(c - b, a - b);
	glm::vec3 nC = glm::cross(d - c, b - c);
	glm::vec3 nD = glm::cross(a - d, c - d);
	m_normalBufferPtr->insertData({
		nA.x, nA.y, nA.z,
		nB.x, nB.y, nB.z,
		nC.x, nC.y, nC.z,
		nD.x, nD.y, nD.z
	});

	m_indexBufferPtr->insertData({
		0, 1, 2,
		2, 3, 0
	});

	m_data.insert(m_data.begin(), {glm::vec4(a, 0.f), glm::vec4(b, 0.f), glm::vec4(c, 0.f), glm::vec4(d, 0.f)});

	m_triangles.emplace_back(glm::vec4(a.x, a.y, a.z, 1.f), glm::vec4(b.x, b.y, b.z, 1.f), glm::vec4(c.x, c.y, c.z, 1.f));
	m_triangles.emplace_back(glm::vec4(a.x, a.y, a.z, 1.f), glm::vec4(c.x, c.y, c.z, 1.f), glm::vec4(d.x, d.y, d.z, 1.f));

}

void Quadrilateral::draw() const {

	m_vaoPtr->draw(static_cast<GLsizei>(m_indexBufferPtr->getSize()));

}
