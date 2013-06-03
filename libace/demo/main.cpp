#include "../libace.h"

ace::Ace *AceEngine = ace::Ace::getEngine();

ace::Mesh   *mesh1;
ace::Mesh   *mesh2;
ace::Mesh   *mesh3;
ace::Mesh   *mesh4;
ace::Light  *light1;
ace::Light  *light2;
ace::Light  *light3;
ace::Light  *light4;

ace::Object *obj1;
ace::Object *obj2;

float light_pos = -10;

void render_loop() {

    light_pos += 0.1f;
    if( light_pos > 10.f ) light_pos = -10.f;

    light1->setPosition( 6, 4, light_pos );
    light2->setPosition( -6, 4, light_pos -5 );

    mesh1->rotate( 0.5f, 1, 0, 0 );
    AceEngine->render();
}  

void input() {
    if( AceEngine->keyPressed( 'E' ) ) AceEngine->nextDebugMode();
}

int main() {
    AceEngine->init( render_loop, input );

    mesh1 = new ace::Mesh();
    mesh1->makeCube();
    mesh2 = new ace::Mesh();
    mesh2->makeQuad();
    mesh3 = new ace::Mesh();
    mesh3->makeQuad();
    mesh4 = new ace::Mesh();
    mesh4->makeCube();
    
    obj1 = new ace::Object( "assets/monkey.obj" );
    obj1->scale( 2 );
    obj1->translate( 0, 0, -10 );

    obj2 = new ace::Object( "assets/house.obj" );
    obj2->scale( 2 );
    obj2->translate( -10, -1.5, 10 );

    light1 = new ace::Light( 1, 1, 0, 1, 5 );
    light2 = new ace::Light( 1, 1, 1, 1, 5 );

    light3 = new ace::Light( 1, 0.3, 0.3, 1, 5 );
    light3->translate( -20, 5, 20 );

    light4 = new ace::Light( 1, 1, 1, 1, 15 );
    light4->translate( -35, 6, 35 );

    mesh1->scale( 1, 1, 1 );

    mesh2->translate( 15, 0, -10 );
    mesh2->scale( 20 );
    mesh2->rotate( -90, 0, 1, 0 );
    
    mesh3->translate( 0, -3, -2 );
    mesh3->scale( 50 );
    mesh3->rotate( -90, 1, 0, 0 );

    mesh4->translate( -20, 5, -15 );
    mesh4->scale( 10 );

    AceEngine->Scene()->add( mesh1 );
    AceEngine->Scene()->add( mesh2 );
    AceEngine->Scene()->add( mesh3 );
    AceEngine->Scene()->add( mesh4 );
    AceEngine->Scene()->add( obj1 );
    AceEngine->Scene()->add( obj2 );
    AceEngine->Scene()->add( light1 );
    AceEngine->Scene()->add( light2 );
    AceEngine->Scene()->add( light3 );
    AceEngine->Scene()->add( light4 );
    AceEngine->start();

    return 0;
}