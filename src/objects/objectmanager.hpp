#pragma once

#include "object.hpp"

#include <memory>
#include <map>

class DrawableManager;
class UpdatableManager;

class ObjectManager {

	public:

		ObjectManager(DrawableManager &, UpdatableManager &);

		template<typename T>
		void add(const std::shared_ptr<T> & ptr) {
			static_assert(std::is_base_of<Object, T>(), "type is not derived from object!");
			add(std::static_pointer_cast<Object>(ptr));
		}

	private:

		void add(const std::shared_ptr<Object> &);

		DrawableManager & m_drawableManager;
		UpdatableManager & m_updatableManager;

		std::map<std::string, std::shared_ptr<Object>> m_objects;

};
