#include "windowthread.hpp"

#include "debug.hpp"

WindowThread::WindowThread(std::shared_ptr<Window> window)
  : std::thread(&WindowThread::windowFunction, window)
{
	Debug::log("Thread started ...");
}

WindowThread::~WindowThread() {
	join();
	Debug::log("Thread joined!");
}

void WindowThread::windowFunction(std::shared_ptr<Window> window) {

	window->start();

}
