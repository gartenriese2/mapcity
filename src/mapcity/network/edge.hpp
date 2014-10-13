#ifndef _EDGE_
#define _EDGE_

#include "node.hpp"

class Edge {

	public:

		Edge();
		Edge(const NodePtr, const NodePtr, float = 0.f);

		unsigned int getID() const { return m_id; }
		float getCost() const { return m_cost; }

		const NodePtr getFrom() const { return m_from; }
		const NodePtr getTo() const { return m_to; }

	protected:

		float m_cost;

	private:

		unsigned int m_id;
		const NodePtr m_from;
		const NodePtr m_to;

};

inline bool operator==(const Edge & lhs, const Edge & rhs){ return lhs.getID() == rhs.getID(); }
inline bool operator!=(const Edge & lhs, const Edge & rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Edge & lhs, const Edge & rhs){ return lhs.getID() < rhs.getID(); }
inline bool operator> (const Edge & lhs, const Edge & rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Edge & lhs, const Edge & rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Edge & lhs, const Edge & rhs){return !operator< (lhs,rhs);}

#endif // _EDGE_
