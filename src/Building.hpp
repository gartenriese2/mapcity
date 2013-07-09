#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "glm.h"
#include <vector>
#include "Object.hpp"
#include "ObjectContainer.hpp"

static const float k_minFloorHeight = 2.8f;
static const float k_maxFloorHeight = 3.5f;

class Building {

	public:

		Building();
		virtual ~Building();

		unsigned long getID() const { return m_ID; }

	protected:
		
		void setShape(const glm::vec3 & c, const glm::vec3 & f, const glm::vec3 & s) { m_center = c; m_front = f; m_side = s; }
		const glm::vec3 & getCenter() const { return m_center; }
		const glm::vec3 & getFront() const { return m_front; }
		const glm::vec3 & getSide() const { return m_side; }

		void setHeight(float, float, int, int);
		float getHeight() const { return m_height; }

		void setColor(const glm::vec3 & c) { m_color = c; }
		const glm::vec3 & getColor() const { return m_color; }
		
		void createObject();
		
		unsigned long m_ID;
		glm::vec3 m_center, m_front, m_side, m_color;
		float m_height;

	private:

		void deleteObject();
		
};

#endif