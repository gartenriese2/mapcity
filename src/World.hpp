#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"

class World {
public:
	World(const int, const int);
	
private:
	
	std::shared_ptr<Map> m_map;

};

#endif