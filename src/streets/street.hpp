#pragma once

#include "../rendering/drawable.hpp"

#include <glm/glm.hpp>

class Street : public Drawable {
	public:
		Street();
};

class StraightStreet : public Street {
	public:
		StraightStreet(const glm::vec3 &, const glm::vec3 &);
	protected:
		void initModelMatrix(float);
	private:
		glm::vec3 m_start, m_end;
};

class StraightSmallStreet : public StraightStreet {
	public:
		StraightSmallStreet(const glm::vec3 &, const glm::vec3 &);
	private:
		const float k_width = 4.f;
};

class StraightMediumStreet : public StraightStreet {
	public:
		StraightMediumStreet(const glm::vec3 &, const glm::vec3 &);
	private:
		const float k_width = 8.f;
};
