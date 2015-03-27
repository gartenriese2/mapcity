#pragma once

#include <string>

class Object {
	public:
		virtual std::string getType() const = 0;
};
