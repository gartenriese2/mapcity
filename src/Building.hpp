#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "../glm-0.9.4.3/glm/glm.hpp"
#include <vector>

class Building {

	static int count;

	public:
		Building();
		virtual ~Building();
		inline int getID() { return this->ID; };
		
	private:
		int ID;
		glm::vec3 center,alignment;
		float height,width,length;
		std::vector<glm::vec3> outline;
	protected:
		void createOutline();
		inline void setCenter(glm::vec3 v) { center = v; }
		inline void setAlignment(glm::vec3 v) { alignment = v; }
		inline void setSize(float h, float w, float l) { height = h; width = w; length = l; }
		
};

#endif