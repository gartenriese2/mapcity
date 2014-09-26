#ifndef _SPHERE_
#define _SPHERE_

#include "object.hpp"
#include "../glmincludes.hpp"
#include "../debug.hpp"

#include <initializer_list>
#include <vector>

class ObjectInterface;

class Sphere : public Object {

	public:
	
		Sphere(Sphere &&) = delete;
		Sphere & operator=(const Sphere &) = delete;
		Sphere & operator=(Sphere &&) = delete;

		virtual ~Sphere() {}

	protected:

		friend ObjectInterface;

		Sphere(const glm::vec3 &, float, unsigned int, unsigned int,
			const glm::vec3 &);
		Sphere(const glm::vec3 &, float, unsigned int, unsigned int,
			const std::initializer_list<glm::vec3> & = {});
		Sphere(const Sphere & t) : Object(t) {}

		std::shared_ptr<Object> getCopy() override;
		std::shared_ptr<Object> getInstance() const override;

		void draw() const;

		unsigned int getType() const { return SPHERE; }

	private:

		Sphere() {}

		void init(const glm::vec3 &, float, unsigned int, unsigned int,
			const std::vector<GLfloat> &);

};

#endif // _SPHERE_