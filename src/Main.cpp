#include "Hexagon.hpp"
#include "DemandFunction.hpp"
#include "Window.hpp"
#include "Map.hpp"
#include "Household.hpp"
#include "Einfamilienhaus.hpp"
#include "Bitmap.hpp"
#include "Terrain.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Landstrasse.hpp"
#include "Bundesstrasse.hpp"
#include "KleinerLaden.hpp"
#include "Mietshaus.hpp"
#include "GrosserLaden.hpp"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <thread>

// BEGIN TEST
// #define LIBACE_TEST // uncomment this to test libace
#ifdef LIBACE_TEST
	#include "../libace/libace.h"
	ace::Ace *AceEngine = ace::Ace::getEngine();

	ace::Mesh 	*mesh1;
	ace::Mesh 	*mesh2;
	ace::Mesh 	*mesh3;
	ace::Mesh 	*mesh4;
	ace::Light  *light1;
	ace::Light  *light2;

	ace::Object *obj1;

	float light_pos = -10;

	void render_loop() {

		light_pos += 0.1f;
		if( light_pos > 10.f ) light_pos = -10.f;

		light1->setPosition( 6, 3, light_pos );
		light2->setPosition( -6, 3, light_pos -5 );

		mesh1->rotate( 0.5f, 1, 0, 0 );
		AceEngine->render();
	}  
	void input() {
		if( AceEngine->keyPressed( 'E' ) ) AceEngine->nextDebugMode();
	}
	void ace_test() {
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
		obj1->translate( 0, 0, -10 );

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

		AceEngine->Scene()->add( mesh1 );
		AceEngine->Scene()->add( mesh2 );
		AceEngine->Scene()->add( mesh3 );
		AceEngine->Scene()->add( mesh4 );
		AceEngine->Scene()->add( obj1 );
		AceEngine->Scene()->add( light1 );
		AceEngine->Scene()->add( light2 );
		AceEngine->start();
	}
#endif

using namespace std;

void findHexagonTest() {

	Hexagon h(glm::vec3(0,0,0));
	cout << h.isInside(glm::vec3(90,0,-15)) << endl;

#ifdef __linux__
	timespec time1, time2;
#endif

	int mapX = 5000;
	int mapZ = 5000;
	Map m(mapX,mapZ);
	
	int falses = 0;
	int counts = 100000;

#ifdef __linux__
	clock_gettime(CLOCK_MONOTONIC, &time1);
#endif

	for (int i = 0; i < counts; i++) {
		float x = (float)(rand() % (mapX*100)) / 100;
		float z = (float)(rand() % (mapZ*100)) / 100;
		// cout << "x: " << x << " ,y: " << y << endl;
		try {
			m.getCorrespondingHexagon(glm::vec3(x,0,-z));
		} catch (const char * msg) {
			cout << msg << endl;
			falses++;
		}
	}

#ifdef __linux__
	clock_gettime(CLOCK_MONOTONIC, &time2);
	cout << "Benötigte Zeit: " << (time2.tv_nsec - time1.tv_nsec)/1000 << " µs." << endl;
#endif
	cout << "Fehlerrate: " << (float)falses / counts * 100 << endl;

}

void demandFunctionTest() {
	DemandFunction d;

	// Industrie
	d.addDemandFunctionStruct(0,0,100, 0.00001f, 0.00002f);
	d.addDemandFunctionStruct(500,500,50, 0.00001f, 0.00002f);

	// Wohnen
	d.addDemandFunctionStruct(-850,0,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-850,10,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-900,0,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-900,10,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-950,0,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-950,10,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1000,0,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1000,10,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1100,0,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1100,10,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1050,0,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1050,10,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1150,0,-30, 0.00001f, 0);
	d.addDemandFunctionStruct(-1150,10,-30, 0.00001f, 0);

	// Gewerbe
	d.addDemandFunctionStruct(-800,0,400, 0.00008f, 0);

	float x;
	float y;

	for (int j = -25; j < 25; ++j) {
		for (int i = -25; i < 25; ++i) {
			x = (float)i * 100;
			y = (float)j * 100;
			int demand = (int)d.addDemandsTogether(x, y);
			cout << demand << "\t";
		}
		cout << "\n";
	}
}

void gameTest() {
	
	int height = 1000, width = 1000;
	Game game(width, height, 1000, 1000);

	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	vectorVec3 path;
	path.push_back(glm::vec3(320,0.1,-232.5));
	path.push_back(glm::vec3(320,0.1,-350));
	Landstrasse l1(path);
	path.clear();
	path.push_back(glm::vec3(320,0.1,-275));
	path.push_back(glm::vec3(262.5,0.1,-275));
	Landstrasse l2(path);
	
	
	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	vectorVec3 zone;
	zone.push_back(glm::vec3(312.5,0.1,-282.5));
	zone.push_back(glm::vec3(290,0.1,-282.5));
	zone.push_back(glm::vec3(290,0.1,-310));
	zone.push_back(glm::vec3(312.5,0.1,-310));
	EinfamilienhausZone ez1(zone);
	zone.clear();
	zone.push_back(glm::vec3(312.5,0.1,-232.5));
	zone.push_back(glm::vec3(290,0.1,-210));
	zone.push_back(glm::vec3(262.5,0.1,-240));
	zone.push_back(glm::vec3(262.5,0.1,-267.5));
	zone.push_back(glm::vec3(312.5,0.1,-267.5));
	MietshausZone mz1(zone);

	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	Einfamilienhaus e1(glm::vec3(305,0,-292.5), glm::vec3(5,0,0), glm::vec3(0,0,-7.5));
	Einfamilienhaus e2(glm::vec3(305,0,-305), glm::vec3(5,0,0), glm::vec3(0,0,-5));
	Einfamilienhaus e3(glm::vec3(295,0,-290), glm::vec3(5,0,0), glm::vec3(0,0,-5));
	Mietshaus m1(glm::vec3(285,0,-235), glm::vec3(12,0,12), glm::vec3(6,0,-6));

	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	zone.clear();
	zone.push_back(glm::vec3(312.5,0.1,-310));
	zone.push_back(glm::vec3(295,0.1,-310));
	zone.push_back(glm::vec3(295,0.1,-330));
	zone.push_back(glm::vec3(312.5,0.1,-330));
	KleinerLadenZone kz1(zone);

	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	KleinerLaden k1(glm::vec3(305,0,-315), glm::vec3(5,0,0), glm::vec3(0,0,-5));

	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	path.clear();
	path.push_back(glm::vec3(320,0.1,-275));
	path.push_back(glm::vec3(420,0.1,-300));
	Landstrasse l3(path);
	
	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	zone.clear();
	zone.push_back(glm::vec3(327.5,0.1,-284));
	zone.push_back(glm::vec3(327.5,0.1,-340));
	zone.push_back(glm::vec3(362.5,0.1,-340));
	zone.push_back(glm::vec3(362.5,0.1,-293));
	GrosserLadenZone gz1(zone);

	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}

	GrosserLaden g1(glm::vec3(345,0,-300), glm::vec3(-15,0,4), glm::vec3(0,0,10));

	for (int i = 0; i < 50000; i++) {
		std::cout << i << "\n";
	}
	
	path.clear();
	path.push_back(glm::vec3(100,1,-100));
	path.push_back(glm::vec3(200,1,-100));
	path.push_back(glm::vec3(200,1,-200));
	path.push_back(glm::vec3(280,1,-200));
	path.push_back(glm::vec3(400,1,-100));
	path.push_back(glm::vec3(500,1,-300));
	Bundesstrasse b1(path);

	game.start();

}

void para() {
	
	for (int i = 0; i < 1000000000; ++i)
	{
		i = 2*i - i;
	}
	cout << "parallel!\n";
	Einfamilienhaus e1(glm::vec3(305,0,-292.5), glm::vec3(5,0,0), glm::vec3(0,0,-7.5));
	Einfamilienhaus e2(glm::vec3(305,0,-305), glm::vec3(5,0,0), glm::vec3(0,0,-5));
	Einfamilienhaus e3(glm::vec3(295,0,-290), glm::vec3(5,0,0), glm::vec3(0,0,-5));
	Einfamilienhaus e4(glm::vec3(300,0,-260), glm::vec3(5,0,5), glm::vec3(5,0,-5));
}

void threadTest() {

	// int height = 1000, width = 1000;
	// Game game(width, height, 1000, 1000);

	thread t1(gameTest);
	thread t2(para);
	t1.join();
	t2.join();

}

void zoneTest() {
	
	Map m(5000,5000);

	vector<glm::vec3> v;
	v.push_back(glm::vec3(201,0,-196));
	v.push_back(glm::vec3(284,0,-111));
	v.push_back(glm::vec3(101,0,-123));
	v.push_back(glm::vec3(98,0,-182));
	

	vector<ResidentialZone> z;
	z.push_back(EinfamilienhausZone(v));
	cout << "ID: " << z[0].getID() << endl;
	cout << "Center: " << z[0].getCenter().x << "|" << z[0].getCenter().z << endl;

	//m.getCorrespondingHexagon(z[0].getCenter()).addResidentialZone(z[0]);

}

void householdTest() {

	int households = 1000000;

	int adults = 0;
	int students = 0;
	int minors = 0;
	int pensioniers = 0;
	int unemployed = 0;
	int worker = 0;
	int children = 0;
	int families = 0;
	int renterhaushalte = 0;
	int wgs = 0;
	int paarhaushalte = 0;
	int singlehaushalte = 0;

	for (int i = 0; i < households; i++) {
		Household h = Household();
		adults += h.getAdults();
		minors += h.getMinors();
		pensioniers += h.getPensioners();
		children += h.getChildren();
		students += h.getStudents();
		unemployed += h.getUnemployed();
		worker += h.getWorker();
		if (h.getChildren() > 0) families++;
		if (h.getPensioners() > 0) renterhaushalte++;
		if (h.getAdults() == h.getStudents() && h.getAdults() > 1) wgs++;
		if (h.getAdults() == 2 && h.getChildren() == 0 && h.getPensioners() == 0) paarhaushalte++;
		if (h.getChildren() == 0 && h.getPensioners() == 0 && h.getAdults() == 1) singlehaushalte++;
	}

	cout << "Es gibt " << families/(float)households*100 << "% Familien (D: 29.0%)" << endl;
	cout << "Es gibt " << renterhaushalte/(float)households*100 << "% Rentnerhaushalte (D: 25.7%)" << endl;
	cout << "Es gibt " << wgs/(float)households*100 << "% WGs (D: 1.5%)" << endl;
	cout << "Es gibt " << paarhaushalte/(float)households*100 << "% Paarhaushalte (D: 18.7%)" << endl;
	cout << "Es gibt " << singlehaushalte/(float)households*100 << "% Singlehaushalte (D: 25.1%)" << endl;
	cout << endl;
	cout << "In den " << households << " Haushalten leben " << adults/(float)(adults+minors)*100 << "% Erwachsene (D: 83.7%)" << endl;
	cout << "In den " << households << " Haushalten leben " << children/(float)(adults+minors)*100 << "% Kinder (auch über 18) (D: 24%)" << endl;
	cout << "In den " << households << " Haushalten leben " << minors/(float)(adults+minors)*100 << "% Kinder (unter 18) (D: 16%)" << endl;
	cout << "In den " << households << " Haushalten leben " << pensioniers/(float)(adults+minors)*100 << "% Rentner (D: 17.5%)" << endl;
	cout << endl;
	cout << "Es gibt " << students/(float)(adults+minors)*100 << "% Studenten (D: 3.1%)" << endl;
	cout << "Es gibt " << unemployed/(float)(adults+minors)*100 << "% dauerhaft Arbeitslose" << endl;
	cout << "Es gibt " << worker/(float)(adults+minors)*100 << "% Arbeitssuchende" << endl;
	cout << "Eine Familie hat durchschnittlich " << children/(float)families << " Kinder, davon " << minors/(float)families << " unter 18." << endl;

}

void terrainTest() {
	Bitmap b("../assets/heightmap.bmp");
	cout << "Height: " << b.getHeight() << ", Width: " << b.getWidth() << "\n";
	Terrain t(b);
	
}

void inheritanceTest() {

	Game game(1000, 1000, 1000, 1000);

	vector<glm::vec3> zone;
	zone.push_back(glm::vec3(201,0,-196));
	zone.push_back(glm::vec3(284,0,-111));
	zone.push_back(glm::vec3(101,0,-123));
	zone.push_back(glm::vec3(98,0,-182));
	EinfamilienhausZone ez1(zone);
	ez1.getResidents();

	std::cout << "Business?: " << ez1.isBusiness() << "\nResidential?: " << ez1.isResidential() << "\n";

	Zone & z1 = ez1;

	std::cout << "Business?: " << z1.isBusiness() << "\nResidential?: " << z1.isResidential() << "\n";

	ResidentialZone & r1 = dynamic_cast<ResidentialZone &>(z1);

	std::cout << "\nResidential?: " << r1.isResidential() << " Residents: " << r1.getResidents() << "\n";

}

int main() {

// BEGIN TEST
#ifdef LIBACE_TEST
	ace_test();
#endif

#ifdef __linux__
	timespec time1;
	clock_gettime(CLOCK_MONOTONIC, &time1);
	srand(static_cast<unsigned int>(time1.tv_nsec));
#endif
	
	// findHexagonTest();
	// demandFunctionTest();
	gameTest();
	// threadTest();
	// zoneTest();
	// householdTest();
	// terrainTest();
	// inheritanceTest();

	return 0;
}