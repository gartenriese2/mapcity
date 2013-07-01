#ifndef ZONE_HPP
#define ZONE_HPP

#include "../glm-0.9.4.3/glm/glm.hpp"
#include <vector>
#include <iostream>
#include "Building.hpp"

class Zone {
	
	static int count;

	public:
		
		Zone();
		virtual ~Zone();

		unsigned long getID() const { return m_ID; }
		glm::vec3 getCenter() const { return m_center; }

	private:
		
				

	protected:
		
		unsigned long m_ID;
		glm::vec3 m_color;
		std::vector<glm::vec3> m_bounding;
		float m_area;
		glm::vec3 m_center;

		void setArea();
		float getArea() const { return m_area; }

		void setCenter();
		

		void setBounding(const std::vector<glm::vec3> b) { m_bounding = b; }
		std::vector<glm::vec3> getBounding() const { return m_bounding; }

		void setColor(const glm::vec3 c) { m_color = c; }
		glm::vec3 getColor() const { return m_color; }

		void createObject();

};

#endif