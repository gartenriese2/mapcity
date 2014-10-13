#include "node.hpp"

#include "edge.hpp"

static unsigned int id {0};

Node::Node()
  : m_id{++id},
  	m_pos{glm::vec3{0.f, 0.f, 0.f}}
{}

Node::Node(const glm::vec3 & pos)
  : m_id{++id},
  	m_pos{pos}
{}

bool Node::addEdge(std::shared_ptr<Edge> edge) {

	if (std::count(m_edgeIDs.begin(), m_edgeIDs.end(), edge->getID()) == 0) {
		m_edgeIDs.push_back(edge->getID());
		return true;
	}

	return false;

}
