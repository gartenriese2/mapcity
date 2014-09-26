#ifndef CUBOIDOBJECT_HPP
#define CUBOIDOBJECT_HPP

#include "Object.hpp"
#include <math.h>

class CuboidObject : public Object {
	
	public:
		
		CuboidObject(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const float, const glm::vec3 & col = glm::vec3(1,1,1));
		~CuboidObject();

		void changeHeight(const float);
		void move(const glm::vec3 &);
		void rotate(const float);

	protected:

		glm::vec3 m_center;
		glm::vec3 m_front;
		glm::vec3 m_side;
		float m_height;
		glm::vec3 m_color;

		virtual void initObject();

};


#endif