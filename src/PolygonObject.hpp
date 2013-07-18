#ifndef POLYGONOBJECT_HPP
#define POLYGONOBJECT_HPP

#include "Object.hpp"

class PolygonObject : public Object {
	
	public:
		
		PolygonObject(const vectorVec3 &, const glm::vec3 &, const glm::vec3 & col = glm::vec3(1,1,1));
		~PolygonObject();

	protected:

		vectorVec3 m_border;
		glm::vec3 m_center;
		glm::vec3 m_color;

		virtual void initObject();

};


#endif