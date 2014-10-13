#include "transitnode.hpp"

TransitNode::TransitNode()
  : Node{}
{}

TransitNode::TransitNode(const glm::vec3 & pos)
  : Node{pos}
{}

void TransitNode::allowTypes(const std::set<unsigned int> & types) {

	m_allowedTypes.insert(types.begin(), types.end());

}
