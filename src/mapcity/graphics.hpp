#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "../engine/engine.hpp"
#include "../engine/handler.hpp"

#include <memory>

class Graphics {

	public:

		void init();

	private:

		std::unique_ptr<Engine> m_enginePtr;
		std::unique_ptr<WindowID> m_windowPtr;

};

#endif // _GRAPHICS_
