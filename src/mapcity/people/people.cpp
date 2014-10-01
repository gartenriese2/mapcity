#include "people.hpp"

People::People()
  : m_age(AGE::INFANT),
  	m_occupation(OCCUPATION::NONE)
{}

People::People(AGE age, OCCUPATION occ)
  : m_age(age),
  	m_occupation(occ)
{}
