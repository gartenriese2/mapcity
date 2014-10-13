#include "buildingdatabase.hpp"

#include "tinyxml2.h"
#include "../../engine/debug.hpp"

#include <cstring>

const std::string k_rootName {"buildingdatabase"};

BuildingDatabase::BuildingDatabase(const std::string & file)
  : Database(file)
{

	m_root = m_doc->RootElement();
	if (m_root == nullptr) {
		Debug::log("No root element found in " + file);
		exit(EXIT_FAILURE);
	}
	
	if (std::strcmp(m_root->Name(), k_rootName.c_str()) != 0) {
		Debug::log(file + " is not a valid " + k_rootName + " file"
			+ "(Missing buildingdatabase root element");
		exit(EXIT_FAILURE);
	}

}
