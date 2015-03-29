#pragma once

#include <MonoEngine/core/log.hpp>

class Object {
	public:
		Object() {
			static std::uint64_t s_id = 0;
			m_ID = ++s_id;
			if (m_ID == 0) {
				LOG_ERROR("Tried to create more objects than possible: "
					+ std::to_string(std::numeric_limits<std::uint64_t>::max()));
			}
		}
		Object(const Object &) = delete;
		Object(Object &&) = delete;
		Object & operator=(const Object &) & = delete;
		Object & operator=(Object  &&) & = delete;
		virtual ~Object() {}
		auto ID() const { return m_ID; }
		virtual std::string getType() const = 0;
	protected:
		std::uint64_t m_ID;
};
