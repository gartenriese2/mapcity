#ifndef _PATH_
#define _PATH_

#include "edge.hpp"
#include "units.hpp"

class Node;

class Path : public Edge {

	public:

		Path(const Node &, const Node &, Speed, Time = 0_s);

	private:

		Speed m_speed;
		Time m_penalty;

};

#endif // _PATH_
