#pragma once

#include "../object.hpp"

#include <vector>

class Terrain : public Object {
	public:
		Terrain(const glm::vec3 &, const glm::vec3 &);
		virtual std::string getType() const override { return "Terrain"; }
		virtual bool isDrawable() const { return true; }
	protected:
		void initDrawables();
	private:
		glm::vec3 m_start, m_end;
};
