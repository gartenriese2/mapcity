#pragma once

#include "object.hpp"

#include <memory>
#include <map>
#include <utility>

class DrawableManager;
class UpdatableManager;

class ObjectManager {

	public:

		ObjectManager(DrawableManager &, UpdatableManager &);

		template<typename T, typename ... Args>
		IDType add(Args && ... args) {
			static_assert(std::is_base_of<Object, T>(), "type is not derived from object!");
			auto ptr = std::make_shared<T>(std::forward<Args>(args) ...);
			add(std::static_pointer_cast<Object>(ptr));
			return ptr->ID();
		}

		template<typename T>
		void remove(const std::shared_ptr<T> & ptr) {
			static_assert(std::is_base_of<Object, T>(), "type is not derived from object!");
			remove(ptr->ID());
		}

		void remove(IDType);
		const std::shared_ptr<Object> & get(IDType);

	private:

		void add(std::shared_ptr<Object> &&);

		DrawableManager & m_drawableManager;
		UpdatableManager & m_updatableManager;

		std::map<IDType, std::shared_ptr<Object>> m_objects;

};
