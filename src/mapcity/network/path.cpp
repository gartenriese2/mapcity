#include "path.hpp"

Path::Path(const NodePtr from, const NodePtr to, unit::speed speed, unit::time penalty)
  : Edge{from, to},
    m_speed{speed},
    m_penalty{penalty}
{

	unit::length distance {glm::length(getFrom()->getPos().get() - getTo()->getPos().get())};
	m_cost = distance / m_speed + m_penalty;

}
