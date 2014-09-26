#ifndef _WINDOWTHREAD_
#define _WINDOWTHREAD_

#include "window.hpp"

#include <thread>
#include <string>
#include <memory>

class WindowThread : public std::thread {

	public:

		WindowThread(std::shared_ptr<Window>);
		WindowThread(const WindowThread &) = delete;
		WindowThread(WindowThread &&) = delete;
		WindowThread & operator=(const WindowThread &) = delete;
		WindowThread & operator=(WindowThread &&) = delete;
		~WindowThread();

	private:

		static void windowFunction(std::shared_ptr<Window>);

};

#endif // _WINDOWTHREAD_