#pragma once

#include "../rendering/drawable.hpp"

class Path : public Drawable {
	public:
		Path() = default;
		virtual std::string getType() const override { return "Path"; }
		virtual glm::vec3 getColor() const override { return {0.f, 0.f, 0.f}; }
		virtual RenderTypeName getRenderType() const = 0;
		virtual bool isDynamic() const override { return false; }
};

class StraightPath : public Path {
	public:
		StraightPath(const glm::vec3 &, const glm::vec3 &);
		virtual RenderTypeName getRenderType() const override { return RenderTypeName::QUAD; }
	protected:
		void initModelMatrix();
		glm::vec3 m_a, m_b;
};
