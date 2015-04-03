#pragma once

#include <MonoEngine/object.hpp>
#include <string>

enum class RenderTypeName : std::uint8_t { QUAD, CUBE, MULTICOLOR_QUAD, MULTICOLOR_CUBE };

struct Drawable {
	const glm::mat4 & getModelMatrix() const {
		return object.getModelMatrix();
	}
	std::string type;
	glm::vec4 color;
	RenderTypeName renderType;
	bool dynamic;
	bool unicolored;
	engine::Object object;
};
