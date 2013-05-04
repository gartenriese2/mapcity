#ifndef HOUSEHOLD_HPP
#define HOUSEHOLD_HPP

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "HouseholdConstants.hpp"
#include "Tree.hpp"

using namespace HouseholdConstants;

class Household {
	public:
		Household();
		Household(float, float, int);
		~Household();

		void printResidents();
		void printTransportation();

		int getMinors();
		int getChildren();
		int getAdults();
		int getPensioners();
		int getStudents();
		int getUnemployed();
		int getWorker();
	private:

		float wealth;

		// People
		int children;
		std::vector<int> people;
		static Tree householdTree;

		// Transportation
		int cars;
		int bikes;

		// Transit Probabilities
		float byCar;
		float byMassTransit;
		float byBike;

		Tree setTreeRealistic();
		void setSimpleTree();
		void createPeople(Node);
		void createSimplePeople(Node n);
		void createRandomPeople();
		void createSubType(std::vector<float>, bool);
		void createPeopleAlternate();
		void createTransportation();
};

#endif