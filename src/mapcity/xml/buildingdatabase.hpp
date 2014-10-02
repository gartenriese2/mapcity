#ifndef _BUILDINGDATABASE_
#define _BUILDINGDATABASE_

#include "database.hpp"

#include <string>

class BuildingDatabase : public Database {

	public:

		BuildingDatabase(const std::string &);

		unsigned int getMinHouseholds(unsigned int);
		unsigned int getMaxHouseholds(unsigned int);

	private:



};

#endif // _BUILDINGDATABASE_
