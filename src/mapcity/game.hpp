#ifndef _GAME_
#define _GAME_

#include "graphics.hpp"

#include <memory>

class Game {

	public:

		void initGraphics();

	private:

		std::unique_ptr<Graphics> m_graphicsPtr;

};

#endif // _GAME_
