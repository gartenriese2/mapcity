#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "glmincludes.hpp"
#include <vector>
#include "ObjectContainer.hpp"
#include "Time.hpp"



class Building {

	public:

		Building();
		virtual ~Building();

		unsigned long getID() const { return m_ID; }
		bool isUnderConstruction() const { return !m_constructionDone; }
		void construct();

		virtual unsigned int getResidents() const { return 0; }

	protected:
		
		static constexpr float k_minFloorHeight = 2.8f;
		static constexpr float k_maxFloorHeight = 3.5f;
		static constexpr float k_constructionHeightPerDay = 1.0f;

		void setShape(const glm::vec3 & c, const glm::vec3 & f, const glm::vec3 & s) { m_center = c; m_front = f; m_side = s; }
		const glm::vec3 & getCenter() const { return m_center; }
		const glm::vec3 & getFront() const { return m_front; }
		const glm::vec3 & getSide() const { return m_side; }

		void setHeight(float, float, int, int);
		float getHeight() const { return m_height; }
		unsigned int getFloors() const { return m_floors; }

		void setColor(const glm::vec3 & c) { m_color = c; }
		const glm::vec3 & getColor() const { return m_color; }
		
		void createObject();
		void changeObjectHeight();
		
		unsigned long m_ID;
		glm::vec3 m_center, m_front, m_side, m_color;
		float m_height;
		float m_actualHeight = 0.01;
		unsigned int m_floors;
		TimePoint m_constructionStart;
		bool m_constructionDone = false;

	private:

		void deleteObject();
		
};

#endif