#include "buildingnode.hpp"

#include <algorithm>

BuildingNode::BuildingNode()
  : Node{}
{}

BuildingNode::BuildingNode(const geom::Point & pos)
  : Node{pos}
{}
