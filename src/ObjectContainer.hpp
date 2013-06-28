#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include "Object.hpp"
#include <map>
#include <memory>

class ObjectContainer {
public:
	ObjectContainer();
private:
	std::map<int, std::shared_ptr<Object>> objectMap;

};

#endif