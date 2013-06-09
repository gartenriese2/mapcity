#include "../libace.h"

ace::Ace *AceEngine = ace::Ace::getEngine();

ace::Mesh   *mesh1;

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

    AceEngine->render();
}  

void input() {
    if( AceEngine->keyPressed( 'E' ) ) AceEngine->nextDebugMode();
}

int main() {
    AceEngine->init( render_loop, input );

    mesh1 = new ace::Mesh();
    mesh1->setTexture( "assets/tex_grass.tga" );
    mesh1->makeQuad();
    mesh1->translate( 0, -3, -2 );
    mesh1->scale( 50 );
    mesh1->rotate( -90, 1, 0, 0 );
    
    obj1 = new ace::Object( "assets/house01.obj" );
    obj1->setTexture( "assets/house01.tga" );
    obj1->scale( 3 );
    obj1->translate( 0, -1.1, -5 );

    obj2 = new ace::Object( "assets/house02.obj" );
    obj2->setTexture( "assets/house02.tga" );
    obj2->translate( -15, -3.5, 15 );

    light1 = new ace::Light( 1, 1, 0, 1, 5 );
    light2 = new ace::Light( 1, 1, 1, 1, 5 );

    light3 = new ace::Light( 1, 0.3, 0.3, 1, 5 );
    light3->translate( -20, 5, 20 );

    light4 = new ace::Light( 1, 1, 1, 1, 15 );
    light4->translate( -35, 6, 35 );

    AceEngine->Scene()->add( mesh1 );
    AceEngine->Scene()->add( obj1 );
    AceEngine->Scene()->add( obj2 );
    AceEngine->Scene()->add( light1 );
    AceEngine->Scene()->add( light2 );
    AceEngine->Scene()->add( light3 );
    AceEngine->Scene()->add( light4 );
    AceEngine->start();

    return 0;
}