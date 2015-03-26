#include "drawable.hpp"

const glm::mat4 & Drawable::getModelMatrix() const {
	return m_object.getModelMatrix();
}
