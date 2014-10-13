#ifndef _PATH_
#define _PATH_

#include "edge.hpp"
#include "units.hpp"

class Node;

class Path : public Edge {

	public:

		Path(const NodePtr, const NodePtr,
			unit::speed, unit::time = 0_s);

	private:

		unit::speed m_speed;
		unit::time m_penalty;

};

#endif // _PATH_
