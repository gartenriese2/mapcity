#ifndef _NETWORK_
#define _NETWORK_

#include "edge.hpp"

#include <memory>
#include <vector>

class Node;

class Network {

	public:

		Network() {}
		Network(const std::vector<std::shared_ptr<Edge>> &);

		void addEdges(const std::vector<std::shared_ptr<Edge>> &);

		std::vector<std::shared_ptr<Edge>> astar(const Node &, const Node &) const;

	private:

		const std::vector<std::shared_ptr<Edge>> getEdgesFromNode(const Node &) const;
		const std::vector<std::shared_ptr<Edge>> getEdgesToNode(const Node &) const;

		std::vector<std::shared_ptr<Edge>> m_edges;

};

#endif // _NETWORK_
