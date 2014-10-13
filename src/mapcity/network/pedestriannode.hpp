#ifndef _PEDESTRIANNODE_
#define _PEDESTRIANNODE_

#include "transitnode.hpp"

class PedestrianNode : public TransitNode {

	public:

		PedestrianNode();
		PedestrianNode(const glm::vec3 &);

};

#endif // _PEDESTRIANNODE_
