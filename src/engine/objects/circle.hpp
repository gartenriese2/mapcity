#ifndef _CIRCLE_
#define _CIRCLE_

#include "object.hpp"
#include "../glmincludes.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Circle : public Object {

	public:
	
		Circle(Circle &&) = delete;
		Circle & operator=(const Circle &) = delete;
		Circle & operator=(Circle &&) = delete;

		virtual ~Circle() {}

	protected:

		friend ObjectInterface;

		Circle(const glm::vec3 &, const glm::vec3 &, float, unsigned int, const glm::vec3 &);
		Circle(const glm::vec3 &, const glm::vec3 &, float, unsigned int, const std::initializer_list<glm::vec3> & = {});
		Circle(const Circle & t) : Object(t) {}

		std::shared_ptr<Object> getCopy() override;
		std::shared_ptr<Object> getInstance() const override;

		void draw() const;

		unsigned int getType() const { return CIRCLE; }

	private:

		Circle() {}

		void init(const glm::vec3 &, const glm::vec3 &, float, unsigned int, const std::vector<GLfloat> &);

};

#endif // _CIRCLE_