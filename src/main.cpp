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

void printAstar(const Network & net, const std::shared_ptr<Node> from, const std::shared_ptr<Node> to) {

	float time {0};
	auto edges = net.astar(from, to);
	for (const auto & edge : edges) {
		Debug::log("Using Edge " + std::to_string(edge->getID()) + " from Node " +
			std::to_string(edge->getFrom()->getID()) + " to Node " +
			std::to_string(edge->getTo()->getID()) + " in " + std::to_string(edge->getCost()) +
			" seconds.");
		time += edge->getCost();
	}
	Debug::log("The whole trip took " + std::to_string(time) + " seconds.");

}

#include "mapcity/network/units.hpp"

void networkTest2() {

	const unit::length distU1BA {200_m};
	const unit::length distBAAmpel1 {400_m};
	const unit::length distAmpel1BB {500_m};
	const unit::length distBBU2 {50_m};
	const unit::length distAmpel {distU1BA + distBAAmpel1};
	const unit::length distU {distAmpel + distAmpel1BB + distBBU2};

	Network network;

	std::shared_ptr<Node> ustation1{new Node({0.f, 5.f, 0.f})};
	std::shared_ptr<Node> ustation1a{new Node({0.f, 0.f, 0.f})};
	std::shared_ptr<Node> ustation1b{new Node({0.f, 10.f, 0.f})};
	std::shared_ptr<Node> ustation2{new Node({distU, 5.f, 0.f})};
	std::shared_ptr<Node> ustation2a{new Node({distU, 0.f, 0.f})};
	std::shared_ptr<Node> ustation2b{new Node({distU, 10.f, 0.f})};

	ResidentialBuilding BA(4, {distU1BA, -5.f, 0.f}, false);
	ResidentialBuilding BB(4, {distU - distBBU2, 15.f, 0.f}, false);
	std::shared_ptr<TransitNode> BAentrance(new TransitNode({distU1BA, 0.f, 0.f}));
	BAentrance->allowTypes({1});
	std::shared_ptr<TransitNode> BAparking(new TransitNode({distU1BA, 5.f, 0.f}));
	BAparking->allowTypes({2});
	std::shared_ptr<TransitNode> BBentrance(new TransitNode({distU - distBBU2, 10.f, 0.f}));
	BBentrance->allowTypes({1});
	std::shared_ptr<TransitNode> BBparking(new TransitNode({distU - distBBU2, 5.f, 0.f}));
	BBparking->allowTypes({2});
	BA.connect(BAentrance, network);
	BB.connect(BBentrance, network);

	std::shared_ptr<Node> ampel1{new Node({distAmpel, 5.f, 0.f})};
	std::shared_ptr<Node> crossingAa{new Node({distAmpel - 5.f, 0.f, 0.f})};
	std::shared_ptr<Node> crossingAb{new Node({distAmpel - 5.f, 10.f, 0.f})};
	std::shared_ptr<Node> crossingBb{new Node({distAmpel + 5.f, 10.f, 0.f})};
	std::shared_ptr<Node> crossingCa{new Node({distAmpel + 5.f, 0.f, 0.f})};

	const unit::speed walkingSpeed {8_kmh};
	const unit::speed drivingSpeed {25_kmh};
	const unit::speed ubahnSpeed {60_kmh};

	const unit::time carGettingTime {1_min};
	const unit::time carParkingTime {2_min};
	const unit::time ubahnWaitingTime {2.5_min};
	const unit::time ampelWaitingTime {20_s};

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
	std::shared_ptr<Edge> BAtoCar(new Path(BAentrance, BAparking, walkingSpeed, carGettingTime));
	std::shared_ptr<Edge> carToBA(new Path(BAparking, BAentrance, walkingSpeed, carParkingTime));
	std::shared_ptr<Edge> BBtoCar(new Path(BBentrance, BBparking, walkingSpeed, carGettingTime));
	std::shared_ptr<Edge> carToBB(new Path(BBparking, BBentrance, walkingSpeed, carParkingTime));
	std::shared_ptr<Edge> carBAtoAmpel(new Path(BAparking, ampel1, drivingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> carAmpelToBA(new Path(ampel1, BAparking, drivingSpeed));
	std::shared_ptr<Edge> carBBtoAmpel(new Path(BBparking, ampel1, drivingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> carAmpelToBB(new Path(ampel1, BBparking, drivingSpeed));

	// walking
	std::shared_ptr<Edge> BAtoU1a(new Path(BAentrance, ustation1a, walkingSpeed));
	std::shared_ptr<Edge> U1atoBA(new Path(ustation1a, BAentrance, walkingSpeed));
	std::shared_ptr<Edge> BAtoCrossingA(new Path(BAentrance, crossingAa, walkingSpeed));
	std::shared_ptr<Edge> crossingAtoBA(new Path(crossingAa, BAentrance, walkingSpeed));
	std::shared_ptr<Edge> crossingAup(new Path(crossingAa, crossingAb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingAdown(new Path(crossingAb, crossingAa, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingCup(new Path(crossingCa, crossingBb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingCdown(new Path(crossingBb, crossingCa, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingBright(new Path(crossingAb, crossingBb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossingBleft(new Path(crossingBb, crossingAb, walkingSpeed, ampelWaitingTime));
	std::shared_ptr<Edge> crossAtoC(new Path(crossingAa, crossingCa, walkingSpeed));
	std::shared_ptr<Edge> crossCtoA(new Path(crossingCa, crossingAa, walkingSpeed));
	std::shared_ptr<Edge> U2atoCrossingC(new Path(ustation2a, crossingCa, walkingSpeed));
	std::shared_ptr<Edge> crossingCtoU2a(new Path(crossingCa, ustation2a, walkingSpeed));
	std::shared_ptr<Edge> U2bToBB(new Path(ustation2b, BBentrance, walkingSpeed));
	std::shared_ptr<Edge> BBtoU2b(new Path(BBentrance, ustation2b, walkingSpeed));
	std::shared_ptr<Edge> crossingBToBB(new Path(crossingBb, BBentrance, walkingSpeed));
	std::shared_ptr<Edge> BBtoCrossingB(new Path(BBentrance, crossingBb, walkingSpeed));
	std::shared_ptr<Edge> U1btoCrossingAB(new Path(ustation1b, crossingAb, walkingSpeed));
	std::shared_ptr<Edge> crossingABtoU1b(new Path(crossingAb, ustation1b, walkingSpeed));

	auto walkingEdges = {BAtoU1a, U1atoBA, BAtoCrossingA, crossingAtoBA, crossingAup, crossingAdown,
		crossingCup, crossingCdown, crossingBright, crossingBleft, crossAtoC, crossCtoA,
		U2atoCrossingC, crossingCtoU2a, U2bToBB, BBtoU2b, crossingBToBB, BBtoCrossingB,
		U1btoCrossingAB, crossingABtoU1b};
	network.addEdges(walkingEdges);

	printAstar(network, BA.getNode(), BB.getNode());

	auto ubahnEdges = {U1aToU1, U1bToU1, U1toU1a, U1toU1b, U1toU2, U2toU1,
		U2aToU2, U2bToU2, U2toU2a, U2toU2b};
	network.addEdges(ubahnEdges);

	printAstar(network, BB.getNode(), BA.getNode());

	network.addEdges({BAtoCar, carToBA, BBtoCar, carToBB, carBAtoAmpel, carAmpelToBA,
		carBBtoAmpel, carAmpelToBB});

	printAstar(network, BA.getNode(), BB.getNode());

}

void buildingTest() {

	Network nw;
	ResidentialBuilding rb(4, {0.f, 0.f, 0.f}, true);
	std::shared_ptr<TransitNode> ptr(new TransitNode({0.f, 20.f, 0.f}));
	ptr->allowTypes({1, 2});
	rb.connect(ptr, nw);

	auto edges = rb.getNode()->getEdgeIDs();
	Debug::log(edges.size());
	auto edge = edges[1];
	Debug::log(edge);

}

#include "mapcity/geom/point.hpp"
#include "mapcity/geom/vector.hpp"
#include "mapcity/geom/segment.hpp"

void geomTest() {

	geom::TPoint2<std::uint8_t> p1 {1, 2};
	geom::TPoint2<std::uint8_t> p2 {3, 0};
	geom::TSegment2<std::uint8_t> s1 {p1, p2};
	std::cout << s1 << std::endl;

	geom::Vec_d v1 {0, 1, 0.5};
	std::cout << v1 << std::endl;

}

int main() {

	//householdTest(10000);
	//residentialTest();
	//networkTest2();
	//buildingTest();
	geomTest();

	return EXIT_SUCCESS;

}
