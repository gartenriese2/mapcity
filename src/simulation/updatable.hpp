#pragma once

#include "../objects/object.hpp"

class Updatable : public virtual Object {

	public:

		virtual void update(float) = 0;
		virtual std::string getType() const = 0;

};
