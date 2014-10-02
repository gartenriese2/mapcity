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
		Debug::log(file + " is not a valid buildingdatabase file"
			+ "(Missing buildingdatabase root element");
		exit(EXIT_FAILURE);
	}

}

unsigned int BuildingDatabase::getMinHouseholds(unsigned int id) {

	ElemPtr ptr = getElement(id);
	if (!ptr) return 0;

	const std::string name {"minHouseholds"};
	unsigned int ret {0};
	
	ElemPtr elem {getElement(ptr->FirstChildElement(), name)};
	if (elem == nullptr) {
		Debug::log("No Element " + name + " found");
		return 0;
	}
	
	if (elem->QueryUnsignedText(&ret) == tinyxml2::XML_NO_ERROR) {
		return ret;
	}

	return 0;

}

unsigned int BuildingDatabase::getMaxHouseholds(unsigned int id) {

	ElemPtr ptr = getElement(id);
	if (!ptr) return 0;

	const std::string name {"maxHouseholds"};
	unsigned int ret {0};
	
	ElemPtr elem {getElement(ptr->FirstChildElement(), name)};
	if (elem == nullptr) {
		Debug::log("No Element " + name + " found");
		return 0;
	}
	
	if (elem->QueryUnsignedText(&ret) == tinyxml2::XML_NO_ERROR) {
		return ret;
	}

	return 0;

}
