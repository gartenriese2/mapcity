#include "objectmanager.hpp"

#include "../rendering/drawablemanager.hpp"
#include "../simulation/updatablemanager.hpp"

#include "streets/street.hpp"

ObjectManager::ObjectManager(DrawableManager & dm, UpdatableManager & um)
  : m_drawableManager{dm},
	m_updatableManager{um}
{}

void ObjectManager::add(const std::shared_ptr<Object> & ptr) {
	m_objects.emplace(ptr->getType(), ptr);
	if (auto drawablePtr = std::dynamic_pointer_cast<Drawable>(ptr)) {
		m_drawableManager.add(drawablePtr);
		if (auto streetPtr = std::dynamic_pointer_cast<Street>(drawablePtr)) {
			m_drawableManager.add(streetPtr->getPaths());
		}
	}
	if (auto updatablePtr = std::dynamic_pointer_cast<Updatable>(ptr)) {
		m_updatableManager.add(updatablePtr);
	}
}
