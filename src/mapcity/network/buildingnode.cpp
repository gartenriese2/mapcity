#include "buildingnode.hpp"

#include <algorithm>

BuildingNode::BuildingNode()
  : Node{}
{}

BuildingNode::BuildingNode(const glm::vec3 & pos)
  : Node{pos}
{}
