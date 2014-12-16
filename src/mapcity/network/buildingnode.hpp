#ifndef _BUILDINGNODE_
#define _BUILDINGNODE_

#include "node.hpp"
#include "../geom/point.hpp"
#include "edge.hpp"

#include <vector>

class BuildingNode : public Node {

	public:

		BuildingNode();
		BuildingNode(const geom::Point &);

};

#endif // _BUILDINGNODE_
