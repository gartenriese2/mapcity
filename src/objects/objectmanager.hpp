#pragma once

#include "object.hpp"

#include <memory>
#include <map>

class DrawableManager;
class UpdatableManager;

class ObjectManager {

	public:

		ObjectManager(DrawableManager &, UpdatableManager &);

		template<typename T, typename ... Args>
		const std::shared_ptr<T> add(const Args & ... args) {
			static_assert(std::is_base_of<Object, T>(), "type is not derived from object!");
			const auto ptr = std::make_shared<T>(args ...);
			add(std::static_pointer_cast<Object>(ptr));
			return ptr;
		}

	private:

		void add(const std::shared_ptr<Object> &);

		DrawableManager & m_drawableManager;
		UpdatableManager & m_updatableManager;

		std::map<std::string, std::shared_ptr<Object>> m_objects;

};
