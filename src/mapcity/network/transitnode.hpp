#ifndef _TRANSITNODE_
#define _TRANSITNODE_

#include "node.hpp"

#include <set>

class TransitNode : public Node {

	public:

		TransitNode();
		TransitNode(const geom::Point &);

		void allowTypes(const std::set<unsigned int> &);

		const std::set<unsigned int> & getAllowedTypes() const { return m_allowedTypes; }

	private:

		std::set<unsigned int> m_allowedTypes;

};

#endif // _TRANSITNODE_
