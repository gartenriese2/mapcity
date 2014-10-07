#include "edge.hpp"

static unsigned int id {0};

Edge::Edge()
  : m_id{0}
{}

Edge::Edge(const Node & a, const Node & b, float cost)
  : m_cost{cost},
  	m_id{++id},
    m_from{a},
    m_to{b}
{}
