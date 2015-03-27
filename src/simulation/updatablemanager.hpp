#pragma once

#include "updatable.hpp"

#include <memory>
#include <map>
#include <vector>

class UpdatableManager {

	public:

		void update(float);
		void add(const std::shared_ptr<Updatable> &);

		template<typename T>
		void add(const std::shared_ptr<T> & ptr) {
			static_assert(std::is_base_of<Updatable, T>::value,
					"adding a Type that is not derived from Updatable");
			add(std::static_pointer_cast<Updatable>(ptr));
		}

	private:

		struct UpdatableType {
			std::vector<std::weak_ptr<Updatable>> objects;
		};
		std::map<std::string, UpdatableType> m_updatables;

};
