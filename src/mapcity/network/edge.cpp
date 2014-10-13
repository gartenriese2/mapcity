#include "edge.hpp"

static unsigned int id {0};

Edge::Edge()
  : m_id{0}
{}

Edge::Edge(const NodePtr a, const NodePtr b, float cost)
  : m_cost{cost},
  	m_id{++id},
    m_from{a},
    m_to{b}
{}
