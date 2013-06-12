#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "glm.h"
#include <vector>
#include "Object.hpp"

class Building {

	static int count;

	public:
		Building();
		virtual ~Building();
		inline int getID() { return ID; }
		inline Object & getObject() { return o; }
		
	private:
		int ID;
		glm::vec3 center,alignment;
		float height,width,length;
		std::vector<glm::vec3> outline;
		Object o;
	protected:
		void createOutline();
		inline void setCenter(const glm::vec3 v) { center = v; }
		inline void setAlignment(const glm::vec3 v) { alignment = v; }
		inline void setSize(const float h, const float w, const float l) { height = h; width = w; length = l; }
		
};

#endif