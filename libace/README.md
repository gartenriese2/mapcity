Libace
======

![libace01](http://jandoerntlein.github.io/screenshots/screen3.jpg)

More screenshots: http://jandoerntlein.github.io/

Changelog
---------
- 03.06.13: upgraded to OpenGL 4, prepared shadow maps, added postprocessing shader (bloom, antialiasing, ssao), fixed light bug, added fps counter
- 13.05.13: killed billboard idea, fixed specular light bug, imported monkey.obj, implemented bloom and prepared SSAO
- 12.05.13: Light class working basically, prepared billboards

TODOS
-----
### General
- setColor() for cubes ;)

### Shaders
Uniforms and attributes can be added easily. Not all data types are supported yet.

### Lights
Lights are implemented directly in the shader code. So far ambient, diffuse and specular lightning are basically
working. But the light goes through solid material and illuminates all meshes that are occluded as well.

### Shadowing
Same problems as with the light. Two ways are possible:
- *Shadow mapping*, easier to implement _and_ working for point lights 
- (*Stencil shadow volumes* (see Carmacks reverse), hard to implement but really nice ;) (see Doom 3), requires
*light volumes*)

### Further improvements
- implement SceneGraph class to render stuff: done, but so far it is just a simple list
- delete TGA loader (glfw already has one: switch!)
- implement class for Terrain (simple LOD: http://wiki.delphigl.com/index.php/Tutorial_Terrain3)
- implement class for different Materials (and bump mapping)
- improve Wavefront Object loader
- particle engine
- post-processing like anti-aliasing, bloom, motion blur


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

Detailed HowTo
--------------
```c
#include "../libace/libace.h" // include libace
ace::Ace *AceEngine = ace::Ace::getEngine(); // get pointer to singleton engine

// create some objects for the scene
ace::Mesh *mesh1; // mesh: can be everything that is drawable
ace::Mesh *mesh2;
ace::Mesh *mesh3;
ace::Mesh *mesh4;
ace::Light *light1; // light: similiar to a mesh, not drawable, not scalable etc
ace::Light *light2;

ace::Object *obj1; // object: mesh which is created from a 3D .obj file

float light_pos = -10;

// main render loop which is called 60x per sec
void render_loop() {

// calculate new light position
light_pos += 0.1f;
if( light_pos > 10.f ) light_pos = -10.f;

// move light
light1->setPosition( 6, 3, light_pos );
light2->setPosition( -6, 3, light_pos -5 );

// rotate the cube mesh around its X-axis
mesh1->rotate( 0.5f, 1, 0, 0 );
// update
AceEngine->render();
}

// keyboard input
void input() {
// step through the gbuffer
if( AceEngine->keyPressed( 'E' ) ) AceEngine->nextDebugMode();
}

// main function
void ace_test() {

// init the engine with the main render loop function and the input function from above
AceEngine->init( render_loop, input );

// create the meshes and objects
mesh1 = new ace::Mesh();
mesh1->makeCube();
mesh2 = new ace::Mesh();
mesh2->makeQuad();
mesh3 = new ace::Mesh();
mesh3->makeQuad();
mesh4 = new ace::Mesh();
mesh4->makeCube();

obj1 = new ace::Object( "assets/monkey.obj" );
obj1->translate( 0, 0, -10 );

// Light( red, green, blue, intensity, radius )
light1 = new ace::Light( 1, 1, 0, 1, 50 );
light2 = new ace::Light( 1, 1, 1, 1, 50 );

mesh1->scale( 1, 1, 1 );

mesh2->translate( 15, 0, -10 );
mesh2->scale( 20 );
mesh2->rotate( -90, 0, 1, 0 );

mesh3->translate( 0, -3, -2 );
mesh3->scale( 50 );
mesh3->rotate( -90, 1, 0, 0 );

mesh4->translate( -20, 5, -15 );
mesh4->scale( 10 );

// add all the objects to the render pool
AceEngine->Scene()->add( mesh1 );
AceEngine->Scene()->add( mesh2 );
AceEngine->Scene()->add( mesh3 );
AceEngine->Scene()->add( mesh4 );
AceEngine->Scene()->add( obj1 );
AceEngine->Scene()->add( light1 );
AceEngine->Scene()->add( light2 );

// start the render_loop function
AceEngine->start();
}
```
