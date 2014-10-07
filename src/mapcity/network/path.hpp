#ifndef _PATH_
#define _PATH_

#include "edge.hpp"

class Node;

class Path : public Edge {

	public:

		Path(const Node &, const Node &, float, float = 0.f);

	private:

		float m_speed;
		float m_penalty;

};

#endif // _PATH_
