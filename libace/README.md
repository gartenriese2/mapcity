Libace
======

Changelog
---------
- 12.05.13: Light class working basically, prepared billboards

HowTo
-----
To get started, create an instance of the engine.    
`ace::Ace *AceEngine = ace::Ace::getEngine();`

Provide a main render loop function and an input function.    
`void render_loop(){ AceEngine->render(); }`   
`void input(){}`

Initialize the engine, create a camera and a window.   
`AceEngine->init( render_loop, input );`

To finally start the engine, type    
`AceEngine->start()`


TODOS
-----
### Shaders
Uniforms and attributes can be added easily. Not all data types are supported yet.

### Lights
Lights are implemented directly in the shader code. So far ambient, diffuse and specular lightning are basically
working. But the light goes through solid material and illuminates all backsides as well. 
Maybe *billboards* or *volumetric lightning* will solve this problem.

### Shadowing
Same problems as with the light. Two ways are possible:
- *Shadow mapping*, easier to implement but not working for point lights so point lights have to be discarded.
- *Stencil shadow volumes* (see Carmacks reverse), hard to implement but quite nice (see Doom 3), requires
*light volumes*

### Further improvements
- implement SceneGraph class to render stuff: done, but so far it is just a simple list
- delete TGA loader and use libpng instead
- implement class for Terrain
- implement class for different Materials (and bump mapping)
- improve Wavefront Object loader
- particle engine
