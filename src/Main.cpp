#include "Hexagon.hpp"
#include "DemandFunction.hpp"
#include "Window.hpp"
#include "Map.hpp"
#include "Zone.hpp"
#include "ResidentialZone.hpp"
#include "Household.hpp"
#include "Einfamilienhaus.hpp"
#include "Bitmap.hpp"
#include "Terrain.hpp"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void findHexagonTest() {

#ifdef __linux__
	timespec time1, time2;
#endif

	int mapX = 5000;
	int mapY = 5000;
	Map m(mapX,mapY);
	
	int falses = 0;
	int counts = 100000;

#ifdef __linux__
	clock_gettime(CLOCK_MONOTONIC, &time1);
#endif

	for (int i = 0; i < counts; i++) {
		float x = (float)(rand() % (mapX*100)) / 100;
		float y = (float)(rand() % (mapY*100)) / 100;
		// cout << "x: " << x << " ,y: " << y << endl;
		try {
			m.getCorrespondingHexagon(glm::vec3(x,y,0));
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
	d.addDemandFunctionStruct(0,0,100, 0.00001, 0.00002);
	d.addDemandFunctionStruct(500,500,50, 0.00001, 0.00002);

	// Wohnen
	d.addDemandFunctionStruct(-850,0,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-850,10,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-900,0,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-900,10,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-950,0,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-950,10,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1000,0,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1000,10,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1100,0,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1100,10,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1050,0,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1050,10,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1150,0,-30, 0.00001, 0);
	d.addDemandFunctionStruct(-1150,10,-30, 0.00001, 0);

	// Gewerbe
	d.addDemandFunctionStruct(-800,0,400, 0.00008, 0);

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

void windowTest() {
	Window w = Window();
	w.createWindow(500, 500);

	w.loop();

	glfwTerminate();
}

void zoneTest() {
	
	Map m(5000,5000);

	vector<glm::vec3> v;
	v.push_back(glm::vec3(201,196,0));
	v.push_back(glm::vec3(284,111,0));
	v.push_back(glm::vec3(101,123,0));
	v.push_back(glm::vec3(98,182,0));
	

	vector<ResidentialZone> z;
	z.push_back(EinfamilienhausZone(v));
	cout << "ID: " << z[0].getID() << endl;
	cout << "Center: " << z[0].getCenter().x << "|" << z[0].getCenter().y << endl;

	m.getCorrespondingHexagon(z[0].getCenter()).addResidentialZone(z[0]);

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

void bebauteZonenTest() {

	Map m(1000,1000);

	vector<glm::vec3> testZone;
	testZone.push_back(glm::vec3(200,200,0));
	testZone.push_back(glm::vec3(250,200,0));
	testZone.push_back(glm::vec3(250,250,0));
	testZone.push_back(glm::vec3(200,250,0));

	Zone * z = new EinfamilienhausZone(testZone);
	Hexagon &hexa = m.getCorrespondingHexagon(z->getCenter());
	hexa.addZone(z);
	// m.getCorrespondingHexagon(z->getCenter()).addZone(z);

	// cout << hexa.countUndevelopedZones() << endl;
	// cout << m.getCorrespondingHexagon(z->getCenter()).countUndevelopedZones() << endl;

	int undeveloped = 0;
	for (int i = 0; i < m.getHexaVector().size(); i++) {
		undeveloped += m.getHexaVector()[i].countUndevelopedZones();
	}

	cout << "Anzahl unbebauter Zonen: " << undeveloped << endl;

	z->addBuilding();
	cout << "Haus gebaut!\n";
	
	undeveloped = 0;
	for (int i = 0; i < m.getHexaVector().size(); i++) {
		undeveloped += m.getHexaVector()[i].countUndevelopedZones();
	}

	cout << "Anzahl unbebauter Zonen: " << undeveloped << endl;

	if ( dynamic_cast<ResidentialBuilding*>( z->getBuildings()[0] ) ) {
		ResidentialBuilding *r = ( ResidentialBuilding* )(z->getBuildings()[0]);
		r->getHouseholds()[0].printResidents();
	}

}

void terrainTest() {
	Bitmap b("../assets/heightmap.bmp");
	cout << "Height: " << b.getHeight() << ", Width: " << b.getWidth() << "\n";
	Terrain t(b);
	for (int i = 0; i < 100; i++) {
		cout << t.getVertices()[i] << "\n";
	}
}

int main() {

#ifdef __linux__
	timespec time1;
	clock_gettime(CLOCK_MONOTONIC, &time1);
	srand(time1.tv_nsec);
#endif

	// findHexagonTest();
	// demandFunctionTest();
	// windowTest();
	// zoneTest();
	// householdTest();
	// bebauteZonenTest();
	terrainTest();

	return 0;
}