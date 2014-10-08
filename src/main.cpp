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

void printAstar(const Network & net, const Node & from, const Node & to) {

	float time {0};
	auto edges = net.astar(from, to);
	for (const auto & edge : edges) {
		Debug::log("Using Edge " + std::to_string(edge->getID()) + " from Node " +
			std::to_string(edge->getFrom().getID()) + " to Node " + 
			std::to_string(edge->getTo().getID()) + " in " + std::to_string(edge->getCost()) + 
			" seconds.");
		time += edge->getCost();
	}
	Debug::log("The whole trip took " + std::to_string(time) + " seconds.");

}

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

	printAstar(net, buildingA, buildingB);

}

void networkTest2() {

	const float distU1BA {200.f};
	const float distBAAmpel1 {400.f};
	const float distAmpel1BB {500.f};
	const float distBBU2 {50.f};
	const float distAmpel {distU1BA + distBAAmpel1};
	const float distU {distAmpel + distAmpel1BB + distBBU2};

	Node ustation1{{0.f, 5.f, 0.f}};
	Node ustation1a{{0.f, 0.f, 0.f}};
	Node ustation1b{{0.f, 10.f, 0.f}};
	Node ustation2{{distU, 5.f, 0.f}};
	Node ustation2a{{distU, 0.f, 0.f}};
	Node ustation2b{{distU, 10.f, 0.f}};

	Node buildingA{{distU1BA, 0.f, 0.f}};
	Node buildingB{{distU - distBBU2, 10.f, 0.f}}; // 8

	Node parkingBA{{distU1BA, 5.f, 0.f}};
	Node parkingBB{{distU - distBBU2, 5.f, 0.f}};

	Node ampel1{{distAmpel, 5.f, 0.f}};
	Node crossingAa{{distAmpel - 5.f, 0.f, 0.f}}; // 12
	Node crossingAb{{distAmpel - 5.f, 10.f, 0.f}};
	Node crossingBb{{distAmpel + 5.f, 10.f, 0.f}};
	Node crossingCa{{distAmpel + 5.f, 0.f, 0.f}}; // 15

	const float walkingSpeed {2.2f}; // 8kmh
	const float drivingSpeed {6.9f}; // 25kmh
	const float ubahnSpeed {16.7f}; // 60kmh

	const float carGettingTime {60.f};
	const float carParkingTime {120.f};
	const float ubahnWaitingTime {150.f};
	const float ampelWaitingTime {20.f};

	// ubahn
	std::shared_ptr<Edge> U1aToU1(new Path(ustation1a, ustation1, walkingSpeed, ubahnWaitingTime));
	std::shared_ptr<Edge> U1bToU1(new Path(ustation1b, ustation1, walkingSpeed, ubahnWaitingTime));
	std::shared_ptr<Edge> U1toU1a(new Path(ustation1, ustation1a, walkingSpeed));
	std::shared_ptr<Edge> U1toU1b(new Path(ustation1, ustation1b, walkingSpeed));
	std::shared_ptr<Edge> U1toU2(new Path(ustation1, ustation2, ubahnSpeed));
	std::shared_ptr<Edge> U2toU1(new Path(ustation2, ustation1, ubahnSpeed));
	std::shared_ptr<Edge> U2aToU2(new Path(ustation2a, ustation2, walkingSpeed, ubahnWaitingTime));
	std::shared_ptr<Edge> U2bToU2(new Path(ustation2b, ustation2, walkingSpeed, ubahnWaitingTime));
	std::shared_ptr<Edge> U2toU2a(new Path(ustation2, ustation2a, walkingSpeed));
	std::shared_ptr<Edge> U2toU2b(new Path(ustation2, ustation2b, walkingSpeed));

	// car
	std::shared_ptr<Edge> BAtoCar(new Path(buildingA, parkingBA, walkingSpeed, carGettingTime)); // 11
	std::shared_ptr<Edge> carToBA(new Path(parkingBA, buildingA, walkingSpeed, carParkingTime));
	std::shared_ptr<Edge> BBtoCar(new Path(buildingB, parkingBB, walkingSpeed, carGettingTime));
	std::shared_ptr<Edge> carToBB(new Path(parkingBB, buildingB, walkingSpeed, carParkingTime));
	std::shared_ptr<Edge> carBAtoAmpel(new Path(parkingBA, ampel1, drivingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> carAmpelToBA(new Path(ampel1, parkingBA, drivingSpeed));
	std::shared_ptr<Edge> carBBtoAmpel(new Path(parkingBB, ampel1, drivingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> carAmpelToBB(new Path(ampel1, parkingBB, drivingSpeed));

	// walking
	std::shared_ptr<Edge> BAtoU1a(new Path(buildingA, ustation1a, walkingSpeed)); // 19
	std::shared_ptr<Edge> U1atoBA(new Path(ustation1a, buildingA, walkingSpeed));
	std::shared_ptr<Edge> BAtoCrossingA(new Path(buildingA, crossingAa, walkingSpeed)); // 21
	std::shared_ptr<Edge> crossingAtoBA(new Path(crossingAa, buildingA, walkingSpeed));
	std::shared_ptr<Edge> crossingAup(new Path(crossingAa, crossingAb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingAdown(new Path(crossingAb, crossingAa, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingCup(new Path(crossingCa, crossingBb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingCdown(new Path(crossingBb, crossingCa, walkingSpeed, ampelWaitingTime)); // 26
	std::shared_ptr<Edge> crossingBright(new Path(crossingAb, crossingBb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingBleft(new Path(crossingBb, crossingAb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossAtoC(new Path(crossingAa, crossingCa, walkingSpeed));
	std::shared_ptr<Edge> crossCtoA(new Path(crossingCa, crossingAa, walkingSpeed));
	std::shared_ptr<Edge> U2atoCrossingC(new Path(ustation2a, crossingCa, walkingSpeed)); // 31
	std::shared_ptr<Edge> crossingCtoU2a(new Path(crossingCa, ustation2a, walkingSpeed));
	std::shared_ptr<Edge> U2bToBB(new Path(ustation2b, buildingB, walkingSpeed));
	std::shared_ptr<Edge> BBtoU2b(new Path(buildingB, ustation2b, walkingSpeed));
	std::shared_ptr<Edge> crossingBToBB(new Path(crossingBb, buildingB, walkingSpeed));
	std::shared_ptr<Edge> BBtoCrossingB(new Path(buildingB, crossingBb, walkingSpeed)); // 36
	std::shared_ptr<Edge> U1btoCrossingAB(new Path(ustation1b, crossingAb, walkingSpeed));
	std::shared_ptr<Edge> crossingABtoU1b(new Path(crossingAb, ustation1b, walkingSpeed));

	Network walking({BAtoU1a, U1atoBA, BAtoCrossingA, crossingAtoBA, crossingAup, crossingAdown,
		crossingCup, crossingCdown, crossingBright, crossingBleft, crossAtoC, crossCtoA,
		U2atoCrossingC, crossingCtoU2a, U2bToBB, BBtoU2b, crossingBToBB, BBtoCrossingB,
		U1btoCrossingAB, crossingABtoU1b});

	printAstar(walking, buildingA, buildingB);

	Network walkingPlusUbahn(walking);
	walkingPlusUbahn.addEdges({U1aToU1, U1bToU1, U1toU1a, U1toU1b, U1toU2, U2toU1,
		U2aToU2, U2bToU2, U2toU2a, U2toU2b});

	printAstar(walkingPlusUbahn, buildingB, buildingA);

	Network all(walkingPlusUbahn);
	all.addEdges({BAtoCar, carToBA, BBtoCar, carToBB, carBAtoAmpel, carAmpelToBA,
		carBBtoAmpel, carAmpelToBB});

	printAstar(all, buildingA, buildingB);

}

int main() {

	//householdTest(10000);
	//residentialTest();
	networkTest2();

	return EXIT_SUCCESS;

}