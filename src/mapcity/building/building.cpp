#include "building.hpp"

#include "../network/path.hpp"

BuildingDatabase Building::s_buildingDatabase = BuildingDatabase("resources/xml/buildings.xml");
TransitDatabase Building::s_transitDatabase = TransitDatabase("resources/xml/transit.xml");

Building::Building(const geom::Point & pos, bool hasParking)
  : m_buildingNode{std::make_shared<BuildingNode>(pos)},
  	m_hasParking{hasParking}
{}

void Building::connect(const std::shared_ptr<TransitNode> node, Network & nw) {

	for (const auto & id : node->getAllowedTypes()) {

		if (s_transitDatabase.hasElement(id, "kmh")) {

			// speed
			unit::speed speed {s_transitDatabase.getValue<float>(id, "kmh")};
			speed.kmhToMs();

			//penalty
			unit::time penalty {0_s};
			if (s_transitDatabase.hasElement(id, "penaltyStart")) {
				penalty = s_transitDatabase.getValue<float>(id, "penaltyStart");
			}
			std::shared_ptr<Path> ptr0(new Path(m_buildingNode, node, speed, penalty));
			m_buildingNode->addEdge(ptr0);

			penalty = 0_s;
			if (s_transitDatabase.hasElement(id, "penaltyEnd")) {
				penalty = s_transitDatabase.getValue<float>(id, "penaltyEnd");
			}
			std::shared_ptr<Path> ptr1(new Path(node, m_buildingNode, speed, penalty));
			node->addEdge(ptr1);

			nw.addEdges({ptr0, ptr1});

		}

	}

}
