#ifndef _PEDESTRIANNODE_
#define _PEDESTRIANNODE_

#include "transitnode.hpp"

class PedestrianNode : public TransitNode {

	public:

		PedestrianNode();
		PedestrianNode(const geom::Point &);

};

#endif // _PEDESTRIANNODE_
