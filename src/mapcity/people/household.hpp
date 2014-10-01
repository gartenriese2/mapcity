#ifndef _HOUSEHOLD_
#define _HOUSEHOLD_

#include "people.hpp"

#include <vector>
#include <memory>

class Household {

	public:

		Household();

		size_t getSize() const { return m_people.size(); }

		size_t getNum(People::AGE) const;
		size_t getNum(People::OCCUPATION) const;

		void addPeople(std::shared_ptr<People>);

		static const Household generateRandomHousehold();
		static const std::vector<Household> generateRandomHouseholds(unsigned int);

	private:

		std::vector<std::shared_ptr<People>> m_people;

};

#endif // _HOUSEHOLD_
