#pragma once

#include "../object.hpp"

#include <vector>

class Building : public Object {
	public:
		Building(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float);
		virtual std::string getType() const = 0;
		virtual bool isDrawable() const { return true; }
	private:
		glm::vec3 m_a, m_b, m_c;
		float m_height;
};

class ResidentialBuilding : public Building {
	public:
		ResidentialBuilding(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float);
		virtual std::string getType() const override { return "ResidentialBuilding"; }
};

class OfficeBuilding : public Building {
	public:
		OfficeBuilding(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float);
		virtual std::string getType() const override { return "OfficeBuilding"; }
};
