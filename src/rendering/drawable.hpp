#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <MonoEngine/object.hpp>

class Drawable {

	public:

		const glm::mat4 & getModelMatrix() const;

	protected:

		std::vector<glm::vec3> m_vertices;
		engine::Object m_object;

};
