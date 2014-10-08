#include "path.hpp"

Path::Path(const Node & from, const Node & to, Speed speed, Time penalty)
  : Edge{from, to},
    m_speed{speed},
    m_penalty{penalty}
{

	Length distance {glm::length(getFrom().getPos() - getTo().getPos())};
	m_cost = distance / m_speed + m_penalty;

}
