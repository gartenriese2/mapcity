#include "Playground.hpp"

static ace::Ace *AceEngine;
static ace::Mesh 	*mesh1;
static ace::Mesh 	*mesh2;
static ace::Mesh 	*mesh3;
static ace::Mesh 	*mesh4;
static ace::Mesh 	*quad1;
static ace::Light  *light1;
long count = 0;

void render_loop(){ 
	
	mesh1->scale(1.f);
	AceEngine->render(); 
}

void input(){
	if( AceEngine->keyPressed( 'E' ) ) AceEngine->nextDebugMode();
}

Playground::Playground() {
	
	AceEngine = ace::Ace::getEngine();
	AceEngine->init( render_loop, input );
	mesh1 = new ace::Mesh();
	mesh2 = new ace::Mesh();
	mesh3 = new ace::Mesh();
	mesh4 = new ace::Mesh();
	mesh1->makeCube();
	mesh2->makeCube();
	mesh3->makeCube();
	mesh4->makeCube();
	mesh2->translate( 5, 0, 0 );
	mesh3->translate( 10, 0, 5 );
	mesh4->translate( 15, 0, 5 );
	AceEngine->Scene()->add( mesh1 );
	AceEngine->Scene()->add( mesh2 );
	AceEngine->Scene()->add( mesh3 );
	AceEngine->Scene()->add( mesh4 );

	quad1 = new ace::Mesh();
	quad1->makeQuad();

	quad1->translate(0, -1.f, 2.5);
	quad1->rotate(90.f, 1.f, 0.f, 0.f);
	quad1->scale(10.f, 1.f, 1.f);
	quad1->translate(0.8, 0, 0);
	AceEngine->Scene()->add( quad1 );

	light1 = new ace::Light( 1, 1, 1, 10, 50 );
	light1->setPosition(-5, 10, 5);
	AceEngine->Scene()->add( light1 );
		
	AceEngine->start();
}

