#include "path.hpp"

Path::Path(const Node & from, const Node & to, float speed, float penalty)
  : Edge{from, to},
    m_speed{speed},
    m_penalty{penalty}
{

	float distance {glm::length(getFrom().getPos() - getTo().getPos())};
	m_cost = distance / m_speed + m_penalty;

}
