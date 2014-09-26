#ifndef _OBJECT_
#define _OBJECT_

#include "../gl/glincludes.hpp"
#include "../glmincludes.hpp"
#include "../gl/vao.hpp"
#include "../gl/vbo.hpp"
#include "../gl/ibo.hpp"

#include <vector>
#include <initializer_list>
#include <memory>

class ObjectInterface;

enum {QUADRILATERAL = 1, CIRCLE, CONE, CUBOID, SPHERE, SPLINE, TRIANGLE};

struct Tri {
	
	glm::vec4 m_a, m_b, m_c;

	Tri(const glm::vec4 & a, const glm::vec4 & b, const glm::vec4 & c) : m_a(a), m_b(b), m_c(c) {}

	const glm::vec4 & A() const { return m_a; }
	const glm::vec4 & B() const { return m_b; }
	const glm::vec4 & C() const { return m_c; }

	void mult(const glm::mat4 & mat) {
		m_a = mat * m_a;
		m_b = mat * m_b;
		m_c = mat * m_c;
	}

};

class Object {

	public:
	
		Object(Object &&) = delete;
		Object & operator=(const Object &) = delete;
		Object & operator=(Object &&) = delete;

		virtual ~Object() {}

		void makeInstance(const Object &);

	protected:

		friend ObjectInterface;

		Object() {};
		Object(const Object &);

		void init();
		void attachBuffers();

		virtual std::shared_ptr<Object> getCopy() = 0;
		virtual std::shared_ptr<Object> getInstance() const = 0;

		virtual void draw() const = 0;
		
		const glm::mat4 & getModelMatrix() const { return m_modelMatrix; }
		void rotate(float, const glm::vec3 &);
		void rotateAround(float, const glm::vec3 &, const glm::vec3 &);
		void move(float, const glm::vec3 &);
		void moveTo(const glm::vec3 &);
		void scale(const glm::vec3 &);
		void scaleColor(float);
		void setColor(const std::initializer_list<glm::vec3> & = {});
		void setColor(const glm::vec3 &);

		bool hasAttachments() const { return !m_attachedObjects.empty(); }

		virtual const std::vector<glm::vec4> & getData() const { return m_data; }
		virtual const std::vector<Tri> & getTriangles() const { return m_triangles; }
		virtual unsigned int getType() const = 0;

		std::shared_ptr<gl::VAO> m_vaoPtr;
		std::shared_ptr<gl::VBO> m_vertexBufferPtr;
		std::shared_ptr<gl::VBO> m_colorBufferPtr;
		std::shared_ptr<gl::VBO> m_normalBufferPtr;
		std::shared_ptr<gl::IBO> m_indexBufferPtr;

		std::vector<glm::vec4> m_data;
		std::vector<Tri> m_triangles;

		glm::mat4 m_modelMatrix;
		glm::mat4 m_scaleMatrix;
		glm::mat4 m_rotationMatrix;
		glm::mat4 m_translationMatrix;

		glm::vec3 m_center;
		glm::vec3 m_actualPosition;
		glm::vec3 m_actualScale;

		std::vector<unsigned long> m_attachedObjects;

		void setCenter(const glm::vec3 &);

		const std::vector<GLfloat> getColorVector(const std::initializer_list<glm::vec3> &, unsigned int) const;
		const std::vector<GLfloat> getColorVector(const glm::vec3 &, unsigned int) const;

		void fillTriangles(const std::vector<GLushort> &, const std::vector<GLfloat> &);

};

#endif // _OBJECT_