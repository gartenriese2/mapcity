#pragma once

#include "../object.hpp"
#include "../../simulation/updatable.hpp"

#include <vector>

class Vehicle : public Updatable {

	public:
		Vehicle(const glm::vec3 &, const glm::vec3 &, const std::string & = "",
				const std::string & = "");
		virtual bool isDrawable() const { return true; }

		void setPosition(const glm::vec3 &);
		const glm::vec3 & getPosition() const;
		void setDirection(const glm::vec3 &);
	protected:
		void initColor(const std::string &);
		void initSize(const std::string &);
		float m_speed;
		glm::vec3 m_pos, m_dir, m_color, m_size;
};
