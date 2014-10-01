#include <stdlib.h>

#include "mapcity/game.hpp"
#include "mapcity/xml/buildingdatabase.hpp"
#include "mapcity/people/household.hpp"
#include "engine/debug.hpp"

int main() {

	Game game;
	//game.initGraphics();

	//BuildingDatabase("resources/xml/test.xml");

	const auto & vec = Household::generateRandomHouseholds(100);
	size_t numPeople {0};
	size_t numInfants {0};
	size_t numKids {0};
	size_t numTeens {0};
	size_t numAdults {0};
	size_t numSeniors {0};
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
	Debug::log("Number of seniors: " + std::to_string(numInfants));

	while(0) {

		/*if (game.graphicsShouldClose()) {
			
			game.terminateGraphics();

			break;

		}*/

	}

	return EXIT_SUCCESS;

}