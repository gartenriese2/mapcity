#ifndef _RENDER_
#define _RENDER_

#include <set>
#include "../debug.hpp"

class Render {

	public:

		Render() {}
		Render(const Render &) = delete;
		Render(Render &&) = delete;
		Render & operator=(const Render &) = delete;
		Render & operator=(Render &&) = delete;

		virtual void draw() = 0;
		virtual void addObjects(std::set<unsigned long>) = 0;
		virtual void removeObject(unsigned long) = 0;
		virtual void changeBaseSize(unsigned int, unsigned int) = 0;

};

#endif // _RENDER_