#ifndef _BUILDING_
#define _BUILDING_

#include "../xml/buildingdatabase.hpp"
#include "../xml/transitdatabase.hpp"
#include "../network/buildingnode.hpp"
#include "../network/transitnode.hpp"
#include "../network/network.hpp"

#include <memory>

class Building {

	public:

		Building() {}
		Building(const geom::Point &, bool = false);

		auto getNode() const { return m_buildingNode; }

		void connect(const std::shared_ptr<TransitNode>, Network &);

	protected:

		static BuildingDatabase s_buildingDatabase;
		static TransitDatabase s_transitDatabase;

		std::shared_ptr<BuildingNode> m_buildingNode;

		bool m_hasParking;

};

#endif // _BUILDING_
