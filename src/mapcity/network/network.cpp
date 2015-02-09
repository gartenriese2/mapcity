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

const std::vector<std::shared_ptr<Edge>> Network::getEdgesFromNode(const NodePtr node) const {

	std::vector<std::shared_ptr<Edge>> vec;

	for (const auto & edge : m_edges) {

		if (edge->getFrom() == node) {

			vec.push_back(edge);

		}

	}

	return vec;

}

const std::vector<std::shared_ptr<Edge>> Network::getEdgesToNode(const NodePtr node) const {

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

float h(const NodePtr a, const NodePtr b) {

	return glm::length(a->getPos().get() - b->getPos().get()) / 100.f;

}

void printPM(const std::map<Node, std::shared_ptr<Edge>> & pathMap) {

	for (const auto & pair : pathMap) {
		Debug::log("Node: " + std::to_string(pair.first.getID()) + ", Edge: "
			+ std::to_string(pair.second->getID()));
	}

}

std::vector<std::shared_ptr<Edge>> createPath(const std::map<NodePtr,
	std::shared_ptr<Edge>> & pathMap, const NodePtr current) {

	for (const auto & pair : pathMap) {

		if (pair.first == current) {

			auto path = createPath(pathMap, pair.second->getFrom());
			path.push_back(pair.second);
			return path;

		}

	}

	return {};

}

std::vector<std::shared_ptr<Edge>> Network::astar(const NodePtr start,
	const NodePtr goal) const {

	std::vector<NodePtr> closed;
	std::vector<NodePtr> open {start};
	std::map<NodePtr, std::shared_ptr<Edge>> came_from;

	std::map<NodePtr, float> g_score {{start, 0.f}};
	auto fStart = g_score[start] + h(start, goal);
	std::map<NodePtr, float> f_score {{start, fStart}};

	while (!open.empty()) {

		std::sort(open.begin(), open.end(), [&](const NodePtr a, const NodePtr b){
			return f_score[a] < f_score[b];
		});
		auto current = open.front();

		if (current == goal) {
			return createPath(came_from, goal);
		}

		open.erase(open.begin());
		closed.push_back(current);

		for (const auto & edge : getEdgesFromNode(current)) {

			auto neighbor = edge->getTo();

			if (isIn(closed, neighbor)) {
				continue;
			}

			auto tentative_g_score = g_score[current] + edge->getCost();

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
