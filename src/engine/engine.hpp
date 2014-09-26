#ifndef _ENGINE_
#define _ENGINE_

#include "windowthread.hpp"
#include "handler.hpp"

#include <string>
#include <map>
#include <memory>

class Engine {

	public:

		Engine();
		Engine(const Engine &) = delete;
		Engine(Engine &&) = delete;
		Engine & operator=(const Engine &) = delete;
		Engine & operator=(Engine &&) = delete;
		~Engine();

		const WindowID createWindow(unsigned int, unsigned int, const std::string & = "Default Title");
		const WindowID createFullscreenWindow(unsigned int, unsigned int, const std::string & = "Default Title");

	private:

		void init();

		std::map<unsigned long, std::unique_ptr<WindowThread>> m_windowThreads;

};

#endif // _ENGINE_