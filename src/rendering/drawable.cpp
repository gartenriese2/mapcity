#include "drawable.hpp"

Drawable::Drawable(Manager & m)
  : m_manager{m}
{

}

Drawable::~Drawable() {

}

const glm::mat4 & Drawable::getModelMatrix() const {
	return m_object.getModelMatrix();
}
