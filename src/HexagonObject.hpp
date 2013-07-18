#ifndef HEXAGONOBJECT_HPP
#define HEXAGONOBJECT_HPP

#include "Object.hpp"

class HexagonObject : public Object {
	
	public:
		
		HexagonObject(const glm::vec3 &, const glm::vec3 &, const glm::vec3 & col = glm::vec3(1,1,1));
		~HexagonObject();

	protected:

		glm::vec3 m_center;
		glm::vec3 m_side;
		glm::vec3 m_color;

		virtual void initObject();

};


#endif