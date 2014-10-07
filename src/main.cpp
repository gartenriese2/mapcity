#include <stdlib.h>

#include "mapcity/game.hpp"
#include "mapcity/building/residentialbuilding.hpp"
#include "mapcity/people/household.hpp"
#include "engine/debug.hpp"

void fillHouseWithRandomHouseholds(ResidentialBuilding & rb) {

	while(rb.getEmptyHouseholds() != 0) {
		rb.moveIn(Household::generateRandomHousehold());
	}

}

void printHouseholds(std::vector<ResidentialBuilding> & rbVec) {

	unsigned int numPeople {0};
	unsigned int numInfants {0};
	unsigned int numKids {0};
	unsigned int numTeens {0};
	unsigned int numAdults {0};
	unsigned int numSeniors {0};

	for (const auto & rb : rbVec) {

		for (const auto & household : rb.getHouseholds()) {

			numPeople += household.getSize();
			numInfants += household.getNum(People::AGE::INFANT);
			numKids += household.getNum(People::AGE::KID);
			numTeens += household.getNum(People::AGE::TEEN);
			numAdults += household.getNum(People::AGE::ADULT);
			numSeniors += household.getNum(People::AGE::SENIOR);

		}

	}

	Debug::log("Number of people created: " + std::to_string(numPeople));
	Debug::log("Number of infants: " + std::to_string(numInfants));
	Debug::log("Number of kids: " + std::to_string(numKids));
	Debug::log("Number of teens: " + std::to_string(numTeens));
	Debug::log("Number of adults: " + std::to_string(numAdults));
	Debug::log("Number of seniors: " + std::to_string(numSeniors));
	
}

void householdTest(unsigned int n) {

	const auto & vec = Household::generateRandomHouseholds(n);
	unsigned int numPeople {0};
	unsigned int numInfants {0};
	unsigned int numKids {0};
	unsigned int numTeens {0};
	unsigned int numAdults {0};
	unsigned int numSeniors {0};
	for (const auto & household : vec) {
		numPeople += household.getSize();
		numInfants += household.getNum(People::AGE::INFANT);
		numKids += household.getNum(People::AGE::KID);
		numTeens += household.getNum(People::AGE::TEEN);
		numAdults += household.getNum(People::AGE::ADULT);
		numSeniors += household.getNum(People::AGE::SENIOR);
	}
	Debug::log("Number of people created: " + std::to_string(numPeople));
	Debug::log("Number of infants: " + std::to_string(numInfants));
	Debug::log("Number of kids: " + std::to_string(numKids));
	Debug::log("Number of teens: " + std::to_string(numTeens));
	Debug::log("Number of adults: " + std::to_string(numAdults));
	Debug::log("Number of seniors: " + std::to_string(numSeniors));

}

void residentialTest() {

	std::vector<ResidentialBuilding> rbVec;
	for (unsigned int i {0}; i < 20; ++i) {
		rbVec.emplace_back(4);
	}
	unsigned int empty {0};
	for (const auto & rb : rbVec) {
		empty += rb.getEmptyHouseholds();
	}
	Debug::log("Empty Households: " + std::to_string(empty));

	for (auto & rb : rbVec) {
		fillHouseWithRandomHouseholds(rb);
	}

	printHouseholds(rbVec);

}

void graphicsTest() {

	Game game;
	game.initGraphics();

	while(1) {

		if (game.graphicsShouldClose()) {
			
			game.terminateGraphics();

			break;

		}

	}

}

#include "mapcity/network/network.hpp"
#include "mapcity/network/node.hpp"
#include "mapcity/network/path.hpp"

void networkTest() {

	Network net;
	const float dist {600.f};
	Node buildingA{{0.f, 0.f, 0.f}};
	Node carParkingA{{0.f, 5.f, 0.f}};
	Node carParkingB{{dist, 5.f, 0.f}};
	Node buildingB{{dist, 0.f, 0.f}};
	std::shared_ptr<Edge> gettingCar(new Path(buildingA, carParkingA, 2.2f, 60.f));
	std::shared_ptr<Edge> driving(new Path(carParkingA, carParkingB, 8.3f));
	std::shared_ptr<Edge> parkingCar(new Path(carParkingB, buildingB, 2.2f, 120.f));
	std::shared_ptr<Edge> walk(new Path(buildingA, buildingB, 2.2f));

	net.addEdges({gettingCar, driving, parkingCar, walk});

	float time {0};
	auto edges = net.astar(buildingA, buildingB);
	for (const auto & edge : edges) {
		Debug::log("Using Edge " + std::to_string(edge->getID()) + " from Node " +
			std::to_string(edge->getFrom().getID()) + " to Node " + 
			std::to_string(edge->getTo().getID()) + " in " + std::to_string(edge->getCost()) + 
			" seconds.");
		time += edge->getCost();
	}
	Debug::log("The whole trip took " + std::to_string(time) + " seconds.");

}

int main() {

	//householdTest(10000);
	//residentialTest();
	networkTest();

	return EXIT_SUCCESS;

}