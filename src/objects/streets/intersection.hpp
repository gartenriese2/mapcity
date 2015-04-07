#pragma once

#include <vector>
#include "../../network/path.hpp"
#include "street.hpp"

class Intersection : public Object {
	public:
		Intersection(const std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>> &);

		virtual std::string getType() const override { return "Intersection"; }
		virtual bool isDrawable() const { return true; }
	protected:
		std::vector<std::shared_ptr<Street>> m_streets;
		std::vector<glm::vec3> m_tangents;
		std::vector<std::shared_ptr<Path>> m_paths;

		glm::vec3 m_pos;

};
