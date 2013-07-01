#ifndef WORLD_HPP
#define WORLD_HPP

#include "ogl.h"
#include <vector>
#include "glm.h"
#include <iostream>
#include "Camera.hpp"
#include "Object.hpp"

#include "Map.hpp"

class World {
public:
	World(const int, const int);
	
private:
	
	std::shared_ptr<Map> m_map;

};

#endif