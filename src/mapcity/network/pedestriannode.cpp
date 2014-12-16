#include "pedestriannode.hpp"

PedestrianNode::PedestrianNode()
  : TransitNode{}
{}

PedestrianNode::PedestrianNode(const geom::Point & pos)
  : TransitNode{pos}
{}
