#pragma once

#include "../objects/object.hpp"

class Path : public Object {
	public:
		Path() = default;
		virtual std::string getType() const override { return "Path"; }

		virtual glm::vec3 getPosition(float) const = 0;
		virtual glm::vec3 getDirection(float) const = 0;
		virtual float advance(const glm::vec3 &, float) const = 0;

		virtual bool isOnPath(const glm::vec3 &) const = 0;
};

class StraightPath : public Path {
	public:
		StraightPath(const glm::vec3 &, const glm::vec3 &);

		virtual glm::vec3 getPosition(float) const override;
		virtual glm::vec3 getDirection(float) const override;
		virtual float advance(const glm::vec3 &, float) const override;

		virtual bool isOnPath(const glm::vec3 &) const override;
	protected:
		void initDrawables();
		glm::vec3 m_a, m_b;
};
