#pragma once

#include "../../rendering/drawable.hpp"
#include "../../simulation/updatable.hpp"

class Vehicle : public Drawable, public Updatable {

	public:
		Vehicle(const glm::vec3 &, const glm::vec3 &, const std::string & = "",
				const std::string & = "");
		virtual glm::vec4 getColor() const override { return glm::vec4(m_color, 1.f); }
		virtual RenderTypeName getRenderType() const override { return RenderTypeName::MULTICOLOR_CUBE; }
		virtual bool isDynamic() const override { return true; }
		virtual bool isUnicolored() const override { return false; }

		void setPosition(const glm::vec3 &);
		const glm::vec3 & getPosition() const;
		void setDirection(const glm::vec3 &);
	protected:
		void initModelMatrix();
		void initColor(const std::string &);
		void initSize(const std::string &);
		float m_speed;
		glm::vec3 m_pos, m_dir, m_color, m_size;
};
