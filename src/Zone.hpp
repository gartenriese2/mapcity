#ifndef ZONE_HPP
#define ZONE_HPP

#include "glm.h"
#include <vector>
#include <iostream>
#include "Building.hpp"

class Zone {

	public:
		
		Zone();
		virtual ~Zone();

		unsigned long getID() const { return m_ID; }
		const glm::vec3 & getCenter() const { return m_center; }

		virtual bool isResidential() const { return false; }
		virtual bool isBusiness() const { return false; }

		virtual void addBuilding() {};

	private:
		
				

	protected:
		
		unsigned long m_ID;
		glm::vec3 m_color;
		vectorVec3 m_bounding;
		float m_area;
		glm::vec3 m_center;

		void setArea();
		const float getArea() const { return m_area; }

		void setCenter();
		

		void setBounding(const vectorVec3 & b) { m_bounding = b; }
		const vectorVec3 & getBounding() const { return m_bounding; }

		void setColor(const glm::vec3 & c) { m_color = c; }
		const glm::vec3 & getColor() const { return m_color; }

		void createObject();

};

#endif