#include <stdlib.h>

#include "mapcity/game.hpp"
#include "mapcity/building/residentialbuilding.hpp"
#include "mapcity/people/household.hpp"
#include "engine/debug.hpp"

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

	ResidentialBuilding rb(2);

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

int main() {

	householdTest(10000);

	return EXIT_SUCCESS;

}