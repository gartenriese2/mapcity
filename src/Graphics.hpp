#ifndef GRAPHICS
#define GRAPHICS

// needs to be included
#include "GraphicsInterface.hpp"

// include the headers you need for the graphics
#include "Window.hpp"

// this is a working sample implementation
class Graphics : public GraphicsInterface {

	const unsigned int STD_WIDTH = 1000;
	const unsigned int STD_HEIGHT = 1000;
	const unsigned int MIN_WIDTH = 640;
	const unsigned int MIN_HEIGHT = 480;
	const unsigned int MAX_WIDTH = 1920;
	const unsigned int MAX_HEIGHT = 1200;

	public:

		static Graphics & instance();
		void setDimensions(const unsigned int, const unsigned int);
		void init();
		void loop();
		
	protected:
		
		static Graphics * pInstance;

		friend class Cleanup;
		class Cleanup {
			public:
				~Cleanup();
		};

		unsigned int m_windowWidth = STD_WIDTH;
		unsigned int m_windowHeight = STD_HEIGHT;

	private:

		Graphics();
		virtual ~Graphics();
		Graphics(const Graphics &);
		Graphics & operator=(const Graphics &);

		shared_ptr<Window> m_window;
	
};

#endif