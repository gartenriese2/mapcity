#ifndef _OBJECTINTERFACE_
#define _OBJECTINTERFACE_

#include "../glmincludes.hpp"
#include "object.hpp"

#include <initializer_list>
#include <map>
#include <memory>

class ObjectInterface {

	public:

		// TRIANGLE
		static void createTriangle(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		static void createTriangle(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});

		// QUADRILATERAL
		static void createQuadrilateral(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		static void createQuadrilateral(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});

		// CIRCLE
		static void createCircle(unsigned long, const glm::vec3 &, const glm::vec3 &, float, unsigned int,
			const glm::vec3 &);
		static void createCircle(unsigned long, const glm::vec3 &, const glm::vec3 &, float, unsigned int,
			const std::initializer_list<glm::vec3> & = {});

		// CUBOID
		static void createCuboid(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		static void createCuboid(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});

		// CONE
		static void createCone(unsigned long, const glm::vec3 &, const glm::vec3 &, float, float, float,
			unsigned int, const glm::vec3 &);
		static void createCone(unsigned long, const glm::vec3 &, const glm::vec3 &, float, float, float,
			unsigned int, const std::initializer_list<glm::vec3> & = {});

		// SPHERE
		static void createSphere(unsigned long, const glm::vec3 &, float, unsigned int, unsigned int,
			const glm::vec3 &);
		static void createSphere(unsigned long, const glm::vec3 &, float, unsigned int, unsigned int,
			const std::initializer_list<glm::vec3> & = {});

		// SPLINE
		static void createSpline(unsigned long, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &, float, float, unsigned int, float, const glm::vec3 &);
		static void createSpline(unsigned long, const std::vector<glm::vec3> &, const glm::vec3 &, float,
			const glm::vec3 &);

		static void copyObject(unsigned long, unsigned long);

		template<class T>
		static void createInstance(unsigned long);


		static void draw(unsigned long);
		static const glm::mat4 & getModelMatrix(unsigned long);
		static void rotate(unsigned long, float, const glm::vec3 &);
		static void rotateAround(unsigned long, float, const glm::vec3 &, const glm::vec3 &);
		static void rotateAround(unsigned long, float, const glm::vec3 &, unsigned long);
		static void move(unsigned long, float, const glm::vec3 &);
		static void moveTo(unsigned long, const glm::vec3 &);
		static void scale(unsigned long, const glm::vec3 &);
		static void scaleColor(unsigned long, float);
		static void setColor(unsigned long, const std::initializer_list<glm::vec3> & = {});
		static void setColor(unsigned long, const glm::vec3 &);

		static void attach(unsigned long, unsigned long);

		static const std::vector<glm::vec4> & getObjectData(unsigned long);
		static const std::vector<Tri> & getObjectTriangles(unsigned long);
		static unsigned int getObjectType(unsigned long);

	private:

		static ObjectInterface & instance() { static ObjectInterface obj; return obj; }
		static void addObject(unsigned long, const std::shared_ptr<Object>);

		unsigned long nextID() const;
		void checkID(unsigned long) const;

		std::map<unsigned long, std::shared_ptr<Object>> m_objects;

};

#endif // _OBJECTINTERFACE_