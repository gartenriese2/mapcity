Libace
======

To get started, create an instance of the engine.
> ace::Ace *AceEngine = ace::Ace::getEngine();

Provide a main render loop function and an input function.
> void render_loop(){}
> void input(){}

Initialize the engine, create a camera and a window.
> AceEngine->init( render_loop, input );

To finally start the engine, type
> AceEngine->start();

TODOS
-----
- think about optimal API design and fix it
- extend Shader class for dynamic attributes and uniforms
- implement SceneGraph class to render stuff
- delete TGA loader and use libpng instead
- implement class for Terrain
- implement class for Light
- improve Wavefront Object loader
