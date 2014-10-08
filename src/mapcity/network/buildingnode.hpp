#ifndef _BUILDINGNODE_
#define _BUILDINGNODE_

#include "node.hpp"
#include "../../engine/glmincludes.hpp"

class BuildingNode : public Node {

	public:

		BuildingNode();
		BuildingNode(const glm::vec3 &);

};

#endif // _BUILDINGNODE_
