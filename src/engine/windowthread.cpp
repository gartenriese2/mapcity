#include "windowthread.hpp"

#include "debug.hpp"

WindowThread::WindowThread(std::shared_ptr<Window> window)
  : std::thread(&WindowThread::windowFunction, window)
{
}

WindowThread::~WindowThread() {
	join();
}

void WindowThread::windowFunction(std::shared_ptr<Window> window) {

	window->start();

}
