#ifndef _LOOP_
#define _LOOP_

#include "glincludes.hpp"
#include "../passes/render.hpp"

#include <queue>
#include <memory>
#include <functional>
#include <map>
#include <set>

class Loop {

	public:

		Loop();
		Loop(const Loop &) = delete;
		Loop(Loop &&) = delete;
		Loop & operator=(const Loop &) = delete;
		Loop & operator=(Loop &&) = delete;

		void start(GLFWwindow *);
		void stop() { m_stop = true; }

		void addRendering(unsigned long id, std::shared_ptr<Render> render) { m_createdRenderings.emplace(id, render); }
		const std::shared_ptr<Render> getRendering(unsigned long id) const { return m_createdRenderings.at(id); }
		void setRendering(const std::shared_ptr<Render> render) { m_rendering = render; }
		void resizeRenderings(unsigned int, unsigned int);
		void addObjectsToRender(unsigned long, std::set<unsigned long>);
		void removeObjectFromRender(unsigned long, unsigned long);
		void addCommand(std::function<void()>);
		void emptyCommands();

		void addKeyEvent(int key, std::function<void()> f) { m_keyEvents.emplace(key, f); }
		void removeKeyEvent(int key) { m_keyEvents.erase(key); }
		void addMouseClickEvent(int key, std::function<void()> f) { m_mouseClickEvents.emplace(key, f); }
		void removeMouseClickEvent(int key) { m_mouseClickEvents.erase(key); }
		void setMouseMoveEvent(std::function<void(double, double)> f) { m_mouseMoveEvent = f; }
		void setScrollEvent(std::function<void(double, double)> f) { m_scrollEvent = f; }

	private:

		void render();

		std::shared_ptr<Render> m_rendering;
		std::map<unsigned long, std::shared_ptr<Render>> m_createdRenderings;
		std::queue<std::function<void()>> m_commands;

		std::map<int, std::function<void()>> m_keyEvents;
		std::map<int, std::function<void()>> m_mouseClickEvents;
		std::function<void(double, double)> m_mouseMoveEvent;
		std::function<void(double, double)> m_scrollEvent;

		bool m_stop;

};

#endif // _LOOP_