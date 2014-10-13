#include "pedestriannode.hpp"

PedestrianNode::PedestrianNode()
  : TransitNode{}
{}

PedestrianNode::PedestrianNode(const glm::vec3 & pos)
  : TransitNode{pos}
{}