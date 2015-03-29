#include "objectmanager.hpp"

#include "../rendering/drawablemanager.hpp"
#include "../simulation/updatablemanager.hpp"

#include "streets/street.hpp"

ObjectManager::ObjectManager(DrawableManager & dm, UpdatableManager & um)
  : m_drawableManager{dm},
	m_updatableManager{um}
{}

void ObjectManager::add(std::shared_ptr<Object> && objPtr) {
	auto pair = m_objects.emplace(objPtr->ID(), std::move(objPtr));
	auto it = pair.first;
	auto ptr = it->second;
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

void ObjectManager::remove(std::uint64_t ID) {
	auto it = m_objects.find(ID);
	if (it != m_objects.end()) {
		m_objects.erase(it);
	} else {
		LOG_WARNING("Tried to remove an Object that wasn't in ObjectManager");
	}
}
