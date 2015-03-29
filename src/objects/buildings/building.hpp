#pragma once

#include "../../rendering/drawable.hpp"

class Building : public Drawable {
	public:
		Building(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float);
		virtual std::string getType() const = 0;
		virtual glm::vec4 getColor() const = 0;
		virtual RenderTypeName getRenderType() const override { return RenderTypeName::CUBE; }
		virtual bool isDynamic() const override { return false; }
	protected:
		void initModelMatrix();
	private:
		glm::vec3 m_a, m_b, m_c;
		float m_height;
};

class ResidentialBuilding : public Building {
	public:
		ResidentialBuilding(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float);
		virtual std::string getType() const override { return "ResidentialBuilding"; }
		virtual glm::vec4 getColor() const override { return {0.f, 0.7f, 0.f, 1.f}; }
};

class OfficeBuilding : public Building {
	public:
		OfficeBuilding(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float);
		virtual std::string getType() const override { return "OfficeBuilding"; }
		virtual glm::vec4 getColor() const override { return {0.f, 0.f, 1.f, 1.f}; }
};
