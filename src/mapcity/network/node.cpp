#include "node.hpp"

static unsigned int id {0};

Node::Node()
  : m_id{++id},
  	m_pos{glm::vec3{0.f, 0.f, 0.f}}
{}

Node::Node(const glm::vec3 & pos)
  : m_id{++id},
  	m_pos{pos}
{}
