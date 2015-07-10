#pragma once

#include "../rendering/drawable.hpp"

#include <MonoEngine/core/log.hpp>

#include <vector>
#include <memory>

using IDType = std::uint64_t;

class Object {
	public:
		Object() {
			static auto s_id {static_cast<std::uint64_t>(0)};
			m_ID = ++s_id;
			if (m_ID == 0) {
				LOG_ERROR("Tried to create more objects than possible: "
					+ std::to_string(std::numeric_limits<IDType>::max()));
			}
		}
		Object(const Object &) = delete;
		Object(Object &&) = default;
		Object & operator=(const Object &) & = delete;
		Object & operator=(Object  &&) & = default;
		virtual ~Object() {}
		auto ID() const { return m_ID; }
		virtual std::string getType() const = 0;
		virtual bool isDrawable() const { return false; }
		const auto & getDrawables() const { return m_drawables; }
	protected:
		IDType m_ID;
		std::vector<std::shared_ptr<Drawable>> m_drawables;
};
