#pragma once

#include "../objects/object.hpp"

#include <MonoEngine/object.hpp>

class Drawable : public virtual Object {

	public:

		enum class RenderTypeName : std::uint8_t { QUAD, CUBE };

		const glm::mat4 & getModelMatrix() const {
			return m_object.getModelMatrix();
		}

		virtual glm::vec3 getColor() const = 0;
		virtual RenderTypeName getRenderType() const = 0;
		virtual bool isDynamic() const = 0;

	protected:

		engine::Object m_object;

};
