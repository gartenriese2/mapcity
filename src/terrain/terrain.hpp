#pragma once

#include "../rendering/drawable.hpp"

class Terrain : public Drawable {
	public:
		Terrain(const glm::vec3 &, const glm::vec3 &);
		virtual std::string getType() const override { return "Terrain"; }
		virtual glm::vec3 getColor() const override { return {0.5f, 1.f, 0.5f}; }
		virtual RenderTypeName getRenderType() const override { return RenderTypeName::QUAD; }
	protected:
		void initModelMatrix();
	private:
		glm::vec3 m_start, m_end;
};
