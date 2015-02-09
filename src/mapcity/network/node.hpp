#ifndef _NODE_
#define _NODE_

#include "../../engine/glmincludes.hpp"
#include "../geom/point.hpp"

#include <memory>
#include <vector>

class Node;
using NodePtr = std::shared_ptr<Node>;

class Edge;

class Node {

	public:

		Node();
		Node(const geom::Point &);

		auto getID() const { return m_id; }
		const auto & getPos() const { return m_pos; }

		bool addEdge(std::shared_ptr<Edge>);
		const auto & getEdgeIDs() const { return m_edgeIDs; }

	protected:

		std::vector<unsigned int> m_edgeIDs;

	private:

		unsigned int m_id;
		geom::Point m_pos;

};

inline bool operator==(const Node & lhs, const Node & rhs){ return lhs.getID() == rhs.getID(); }
inline bool operator!=(const Node & lhs, const Node & rhs){ return !operator==(lhs,rhs); }
inline bool operator< (const Node & lhs, const Node & rhs){ return lhs.getID() < rhs.getID(); }
inline bool operator> (const Node & lhs, const Node & rhs){ return  operator< (rhs,lhs); }
inline bool operator<=(const Node & lhs, const Node & rhs){ return !operator> (lhs,rhs); }
inline bool operator>=(const Node & lhs, const Node & rhs){ return !operator< (lhs,rhs); }

#endif // _NODE_
