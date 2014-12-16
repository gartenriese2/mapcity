#include "node.hpp"

#include "edge.hpp"

static unsigned int id {0};

Node::Node()
  : m_id{++id}
{}

Node::Node(const geom::Point & pos)
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
