#ifndef _NODE_
#define _NODE_

#include "../../engine/glmincludes.hpp"

class Node {

	public:

		Node();
		Node(const glm::vec3 &);

		unsigned int getID() const { return m_id; }
		const glm::vec3 & getPos() const { return m_pos; }

	private:

		unsigned int m_id;
		glm::vec3 m_pos;

};

inline bool operator==(const Node & lhs, const Node & rhs){ return lhs.getID() == rhs.getID(); }
inline bool operator!=(const Node & lhs, const Node & rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Node & lhs, const Node & rhs){ return lhs.getID() < rhs.getID(); }
inline bool operator> (const Node & lhs, const Node & rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Node & lhs, const Node & rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Node & lhs, const Node & rhs){return !operator< (lhs,rhs);}

#endif // _NODE_
