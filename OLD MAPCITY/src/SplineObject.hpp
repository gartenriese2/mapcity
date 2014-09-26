#ifndef SPLINEOBJECT_HPP
#define SPLINEOBJECT_HPP

#include "Object.hpp"

class SplineObject : public Object {
	
	public:
		
		SplineObject(const vectorVec3 &, const float, const glm::vec3 & col = glm::vec3(1,1,1));
		~SplineObject();

	protected:

		vectorVec3 m_path;
		float m_width;
		glm::vec3 m_color;

		virtual void initObject();

};


#endif