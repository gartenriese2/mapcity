#include "buildingdatabase.hpp"

#include "tinyxml2.h"
#include "../../engine/debug.hpp"

#include <cstring>

const std::string k_rootName {"buildingdatabase"};

BuildingDatabase::BuildingDatabase(const std::string & file)
  : Database(file)
{

	tinyxml2::XMLElement * elem = m_doc.RootElement();
	
	if (std::strcmp(elem->Name(), k_rootName.c_str()) != 0) {
		Debug::log(file + " is not a valid buildingdatabase file"
			+ "(Missing buildingdatabase root element");
		return;
	}

}
