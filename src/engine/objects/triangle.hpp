#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "object.hpp"
#include "../glmincludes.hpp"
#include "../debug.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Triangle : public Object {

	public:
	
		Triangle(Triangle &&) = delete;
		Triangle & operator=(const Triangle &) = delete;
		Triangle & operator=(Triangle &&) = delete;

		virtual ~Triangle() {}

	protected:

		friend ObjectInterface;

		Triangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);
		Triangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});
		Triangle(const Triangle & t) : Object(t) {}

		std::shared_ptr<Object> getCopy() override;
		std::shared_ptr<Object> getInstance() const override;

		void draw() const;

		unsigned int getType() const { return TRIANGLE; }

	private:

		Triangle() {}

		void init(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const std::vector<GLfloat> &);

};

#endif // _TRIANGLE_