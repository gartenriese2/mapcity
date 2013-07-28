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

		unsigned long m_queriedID = 0;
		void setQueriedID(unsigned long id) { m_queriedID = id; }

};

#endif