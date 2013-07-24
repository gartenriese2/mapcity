#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"
#include "InputHandler.hpp"

class World {
	public:
		
		World(const int, const int);

		void loop(bool &);
		
	protected:
		
		std::shared_ptr<Map> m_map;

		void checkInput();

};

#endif