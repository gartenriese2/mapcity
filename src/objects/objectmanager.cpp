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
	if (ptr->isDrawable()) {
		for (const auto & drawable : ptr->getDrawables()) {
			m_drawableManager.add(drawable);
		}
	}
	if (auto streetPtr = std::dynamic_pointer_cast<Street>(ptr)) {
		for (const auto & path : streetPtr->getPaths()) {
			for (const auto & drawable : path->getDrawables()) {
				m_drawableManager.add(drawable);
			}
		}
	}
	if (auto updatablePtr = std::dynamic_pointer_cast<Updatable>(ptr)) {
		m_updatableManager.add(updatablePtr);
	}
}

void ObjectManager::remove(IDType ID) {
	auto it = m_objects.find(ID);
	if (it != m_objects.end()) {
		m_objects.erase(it);
	} else {
		LOG_WARNING("Tried to remove an Object that wasn't in ObjectManager");
	}
}

const std::shared_ptr<Object> & ObjectManager::get(const IDType ID) {
	if (m_objects.count(ID) == 0) {
		LOG_ERROR("Trying to get non existant Object!");
	}
	return m_objects.at(ID);
}
