#include "network.hpp"

#include "../../engine/debug.hpp"

#include <algorithm>
#include <map>

Network::Network(const std::vector<std::shared_ptr<Edge>> & edges)
  : m_edges{edges}
{}

void Network::addEdges(const std::vector<std::shared_ptr<Edge>> & edges) {

	m_edges.insert(m_edges.end(), edges.begin(), edges.end());

}

const std::vector<std::shared_ptr<Edge>> Network::getEdgesFromNode(const Node & node) const {

	std::vector<std::shared_ptr<Edge>> vec;

	for (const auto & edge : m_edges) {

		if (edge->getFrom() == node) {

			vec.push_back(edge);

		}

	}

	return vec;

}

const std::vector<std::shared_ptr<Edge>> Network::getEdgesToNode(const Node & node) const {

	std::vector<std::shared_ptr<Edge>> vec;

	for (const auto & edge : m_edges) {

		if (edge->getTo() == node) {

			vec.push_back(edge);

		}

	}

	return vec;

}

template<class T>
bool isIn(const std::vector<T> & vec, T elem) {

	return std::count(vec.begin(), vec.end(), elem) > 0;

}

float h(const Node & a, const Node & b) {

	return glm::length(a.getPos() - b.getPos()) / 100.f;

}

void printPM(const std::map<Node, std::shared_ptr<Edge>> & pathMap) {
	Debug::log("Printing PathMap");
	for (const auto & pair : pathMap) {
		Debug::log("Node: " + std::to_string(pair.first.getID()) + ", Edge: "
			+ std::to_string(pair.second->getID()));
	}

}

std::vector<std::shared_ptr<Edge>> createPath(const std::map<Node,
	std::shared_ptr<Edge>> & pathMap, const Node & current) {
//printPM(pathMap);
//exit(0);
	for (const auto & pair : pathMap) {
		
		if (pair.first == current) {
			
			auto path = createPath(pathMap, pair.second->getFrom());
			path.push_back(pair.second);
			return path;

		}

	}

	return {};

}

std::vector<std::shared_ptr<Edge>> Network::astar(const Node & start, const Node & goal) const {

	std::vector<Node> closed;
	std::vector<Node> open {start};
	std::map<Node, std::shared_ptr<Edge>> came_from;

	std::map<Node, float> g_score {{start, 0.f}};
	float fStart {g_score[start] + h(start, goal)};
	std::map<Node, float> f_score {{start, fStart}};

	while (!open.empty()) {
		
		std::sort(open.begin(), open.end(), [&](const Node & a, const Node & b){
			return f_score[a] < f_score[b];
		});
		Node current = open.front();
		
		if (current == goal) {
			return createPath(came_from, goal);
		}

		open.erase(open.begin());
		closed.push_back(current);
		//Debug::log("Current Node: " + std::to_string(current.getID()));
		for (const auto & edge : getEdgesFromNode(current)) {

			Node neighbor {edge->getTo()};
			
			if (isIn(closed, neighbor)) {
				continue;
			}

			float tentative_g_score {g_score[current] + edge->getCost()};

			if (!isIn(open, neighbor) ||
				g_score.count(neighbor) == 0 ||
				tentative_g_score < g_score[neighbor]) {

				came_from[neighbor] = edge;
				
				g_score[neighbor] = tentative_g_score;
				f_score[neighbor] = g_score[neighbor] + h(neighbor, goal);

				if (!isIn(open, neighbor)) {
					open.push_back(neighbor);
				}

			}

		}

	}

	return {};

}
