Libace
======

To get started, create an instance of the engine.
> ace::Ace *AceEngine = ace::Ace::getInstance();

Provide a main render loop function and an input function.
> void render_loop(){}
> void input(){}

Initialize the engine, create a camera and a window.
> AceEngine->AceInit( render_loop, input );

To finally start the engine, type
> AceEngine->AceMainLoop();


