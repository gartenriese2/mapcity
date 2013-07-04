#ifndef HOUSEHOLD_HPP
#define HOUSEHOLD_HPP

#include <iostream>
#include <vector>

#include "HouseholdConstants.hpp"
#include "Tree.hpp"

using namespace HouseholdConstants;

class Household {
	
	public:

		Household();
		Household(const float, const float, const int);
		~Household();

		void printResidents() const;
		void printTransportation() const;

		int getMinors() const;
		int getChildren() const;
		int getAdults() const;
		int getPensioners() const;
		int getStudents() const;
		int getUnemployed() const;
		int getWorker() const;

	private:

		float wealth;

		// People
		int children;
		std::vector<int> people;

		// Transportation
		int cars;
		int bikes;

		// Transit Probabilities
		float byCar;
		float byMassTransit;
		float byBike;

		void createRandomPeople();
		void createTransportation();

};

#endif