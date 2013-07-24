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
	
	int height = 1024, width = 1024;
	Game game(width, height, 1000, 1000);

	Time::instance().setIngameSpeed(Time::FASTFORWARD);

	Time::instance().waitMilliseconds(1000);

	vectorVec3 path;
	path.push_back(glm::vec3(320,0.01,-232.5));
	path.push_back(glm::vec3(320,0.01,-350));
	Landstrasse l1(path);
	path.clear();
	path.push_back(glm::vec3(320,0.01,-275));
	path.push_back(glm::vec3(262.5,0.01,-275));
	Landstrasse l2(path);
	
	
	Time::instance().waitMilliseconds(1000);

	vectorVec3 zone;
	zone.push_back(glm::vec3(312.5,0.01,-282.5));
	zone.push_back(glm::vec3(290,0.01,-282.5));
	zone.push_back(glm::vec3(290,0.01,-310));
	zone.push_back(glm::vec3(312.5,0.01,-310));
	EinfamilienhausZone ez1(zone);
	zone.clear();
	zone.push_back(glm::vec3(312.5,0.01,-232.5));
	zone.push_back(glm::vec3(290,0.01,-210));
	zone.push_back(glm::vec3(262.5,0.01,-240));
	zone.push_back(glm::vec3(262.5,0.01,-267.5));
	zone.push_back(glm::vec3(312.5,0.01,-267.5));
	MietshausZone mz1(zone);

	Time::instance().waitMilliseconds(1000);

	zone.clear();
	zone.push_back(glm::vec3(312.5,0.01,-310));
	zone.push_back(glm::vec3(295,0.01,-310));
	zone.push_back(glm::vec3(295,0.01,-330));
	zone.push_back(glm::vec3(312.5,0.01,-330));
	KleinerLadenZone kz1(zone);

	Time::instance().waitMilliseconds(1000);

	path.clear();
	path.push_back(glm::vec3(320,0.01,-275));
	path.push_back(glm::vec3(420,0.01,-300));
	Landstrasse l3(path);
	
	Time::instance().waitMilliseconds(1000);

	zone.clear();
	zone.push_back(glm::vec3(327.5,0.01,-284));
	zone.push_back(glm::vec3(327.5,0.01,-340));
	zone.push_back(glm::vec3(362.5,0.01,-340));
	zone.push_back(glm::vec3(362.5,0.01,-293));
	GrosserLadenZone gz1(zone);	

	Time::instance().waitMilliseconds(1000);
	
	path.clear();
	path.push_back(glm::vec3(200,0.01,-200));
	path.push_back(glm::vec3(300,0.01,-200));
	path.push_back(glm::vec3(370,0.01,-250));
	path.push_back(glm::vec3(370,0.01,-400));
	Bundesstrasse b1(path);

	Time::instance().waitMilliseconds(1000);

	Einfamilienhaus e1(glm::vec3(305,0,-292.5), glm::vec3(5,0,0), glm::vec3(0,0,-7.5));
	Einfamilienhaus e2(glm::vec3(305,0,-305), glm::vec3(5,0,0), glm::vec3(0,0,-5));
	Einfamilienhaus e3(glm::vec3(295,0,-290), glm::vec3(5,0,0), glm::vec3(0,0,-5));
	Mietshaus m1(glm::vec3(285,0,-235), glm::vec3(12,0,12), glm::vec3(6,0,-6));
	KleinerLaden k1(glm::vec3(305,0,-315), glm::vec3(5,0,0), glm::vec3(0,0,-5));
	GrosserLaden g1(glm::vec3(345,0,-300), glm::vec3(-15,0,4), glm::vec3(0,0,10));

	glm::vec3 carPos = glm::vec3(317.5,0,-340);
	glm::vec3 mov = glm::vec3(0,0,0.1);
	float turn = 0.f;
	unsigned long car = ObjectContainer::instance().addCuboid(carPos, glm::vec3(1.3,0,0), glm::vec3(0,0,-2.5), 1.5, glm::vec3(0.5,0,0));

	while(m1.isUnderConstruction()) {
		
		Time::instance().waitMilliseconds(10);
		m1.construct();
		e1.construct();
		e2.construct();
		e3.construct();
		k1.construct();
		g1.construct();


		// carPos += mov;

		// if (carPos.z > -250 && turn != 180.f) {
		// 	ObjectContainer::instance().rotateCuboid(car, 1.2f);
		// 	turn += 1.2f;
		// 	// mov = -mov;
		// } else if (carPos.z < -340 && turn != 180.f) {
		// 	ObjectContainer::instance().rotateCuboid(car, 1.2f);
		// 	turn += 1.2f;
		// 	// mov = -mov;
		// }
		// if (turn == 180.f) turn = 0.f;
		// ObjectContainer::instance().moveCuboid(car, mov);
		
	}	

	game.end();

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

#ifdef __linux__
	timespec time1;
	clock_gettime(CLOCK_MONOTONIC, &time1);
	srand(static_cast<unsigned int>(time1.tv_nsec));
#endif
	
	// findHexagonTest();
	// demandFunctionTest();
	gameTest();
	// zoneTest();
	// householdTest();
	// terrainTest();
	// inheritanceTest();

	return 0;
}