#ifndef _NODE_
#define _NODE_

#include "../../engine/glmincludes.hpp"

#include <memory>
#include <vector>

class Node;
using NodePtr = std::shared_ptr<Node>;

class Edge;

class Node {

	public:

		Node();
		Node(const glm::vec3 &);

		unsigned int getID() const { return m_id; }
		const glm::vec3 & getPos() const { return m_pos; }

		bool addEdge(std::shared_ptr<Edge>);
		const std::vector<unsigned int> & getEdgeIDs() const { return m_edgeIDs; }

	protected:

		std::vector<unsigned int> m_edgeIDs;

	private:

		unsigned int m_id;
		glm::vec3 m_pos;

};

inline bool operator==(const Node & lhs, const Node & rhs){ return lhs.getID() == rhs.getID(); }
inline bool operator!=(const Node & lhs, const Node & rhs){ return !operator==(lhs,rhs); }
inline bool operator< (const Node & lhs, const Node & rhs){ return lhs.getID() < rhs.getID(); }
inline bool operator> (const Node & lhs, const Node & rhs){ return  operator< (rhs,lhs); }
inline bool operator<=(const Node & lhs, const Node & rhs){ return !operator> (lhs,rhs); }
inline bool operator>=(const Node & lhs, const Node & rhs){ return !operator< (lhs,rhs); }

#endif // _NODE_
