#include "updatablemanager.hpp"

void UpdatableManager::update(const float step) {
	for (const auto & updatablePair : m_updatables) {
		const auto & updateType = updatablePair.second;
		if (updateType.objects.size() == 0) {
			continue;
		}
		for (auto & ptr : updateType.objects) {
			ptr.lock()->update(step);
		}
	}
}

void UpdatableManager::add(const std::shared_ptr<Updatable> & updatable) {
	const auto type = updatable->getType();
	m_updatables[type].objects.emplace_back(updatable);
}
