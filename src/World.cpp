#include "World.hpp"

World::World(const int height, const int width) {
	
	m_map = std::make_shared<Map>(height, width);
	
}