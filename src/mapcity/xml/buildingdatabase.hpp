#ifndef _BUILDINGDATABASE_
#define _BUILDINGDATABASE_

#include "database.hpp"

#include <string>

class BuildingDatabase : public Database {

	public:

		BuildingDatabase(const std::string &);

		unsigned int getUnsignedValue(unsigned int, const std::string &) const;
		bool hasElement(unsigned int, const std::string &) const;

	private:



};

#endif // _BUILDINGDATABASE_
