#ifndef _PEOPLE_
#define _PEOPLE_

#include <cstdint>

class People {

	public:

		enum class AGE : std::uint8_t { INFANT, KID, TEEN, ADULT, SENIOR };
		enum class OCCUPATION : std::uint8_t { NONE, WORK, PRESCHOOL, SCHOOL, UNIVERSITY };

		People();
		People(AGE, OCCUPATION);

		AGE getAge() const { return m_age; }
		OCCUPATION getOccupation() const { return m_occupation; }

	private:

		AGE m_age;
		OCCUPATION m_occupation;

};

#endif // _PEOPLE_
