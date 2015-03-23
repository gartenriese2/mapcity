#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <MonoEngine/object.hpp>

class Drawable {

	public:

		enum class RenderTypeName : std::uint8_t { QUAD, CUBE };

		const glm::mat4 & getModelMatrix() const;

		virtual std::string getType() const = 0;
		virtual glm::vec3 getColor() const = 0;
		virtual RenderTypeName getRenderType() const = 0;

	protected:

		engine::Object m_object;

};
