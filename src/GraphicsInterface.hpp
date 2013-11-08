#ifndef GRAPHICSINTERFACE
#define GRAPHICSINTERFACE

class GraphicsInterface {

	protected:

		// initialize OpenGL contexts and other things (window,camera,shader,etc.)
		virtual void init() = 0;

		// render loop
		virtual void loop() = 0;

};

#endif