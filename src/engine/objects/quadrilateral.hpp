#ifndef _QUADRILATERAL_
#define _QUADRILATERAL_

#include "object.hpp"
#include "../glmincludes.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Quadrilateral : public Object {

	public:
	
		Quadrilateral(Quadrilateral &&) = delete;
		Quadrilateral & operator=(const Quadrilateral &) = delete;
		Quadrilateral & operator=(Quadrilateral &&) = delete;

		virtual ~Quadrilateral() {}

	protected:

		friend ObjectInterface;

		Quadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		Quadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});
		Quadrilateral(const Quadrilateral & q) : Object(q) {}

		std::shared_ptr<Object> getCopy() override;
		std::shared_ptr<Object> getInstance() const override;

		void draw() const;

		unsigned int getType() const { return QUADRILATERAL; }

	private:

		Quadrilateral() {}

		void init(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::vector<GLfloat> &);

};

#endif // _QUADRILATERAL_