#ifndef _HOUSEHOLD_
#define _HOUSEHOLD_

#include "people.hpp"

#include <vector>
#include <memory>

class Household {

	public:

		Household();

		auto getSize() const { return static_cast<unsigned int>(m_people.size()); }

		unsigned int getNum(People::AGE) const;
		unsigned int getNum(People::OCCUPATION) const;

		void addPeople(std::shared_ptr<People>);

		static const Household generateRandomHousehold();
		static const std::vector<Household> generateRandomHouseholds(unsigned int);

	private:

		std::vector<std::shared_ptr<People>> m_people;

};

#endif // _HOUSEHOLD_
