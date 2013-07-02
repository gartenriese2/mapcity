#ifndef PATH_HPP
#define PATH_HPP

#include "glm.h"
#include <vector>

#include "ObjectContainer.hpp"

class Path {

	public:
		
		Path();
		virtual ~Path();

		unsigned long getID() const { return m_ID; }

	protected:

		unsigned long m_ID;
		glm::vec3 m_color;
		vectorVec3 m_pts;
		float m_width;

		void setWaypoints(const vectorVec3 pts) { m_pts = pts; }

		void setWidth(const float w) { m_width = w; }

		void setColor(const glm::vec3 col) { m_color = col; }

		void createObject();

};

#endif