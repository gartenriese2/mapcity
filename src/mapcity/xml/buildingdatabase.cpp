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

unsigned int BuildingDatabase::getUnsignedValue(unsigned int id,
	const std::string & name) const {

	ElemPtr ptr = getElement(id);
	if (ptr == nullptr) return 0;

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

bool BuildingDatabase::hasElement(unsigned int id, const std::string & name) const {

	ElemPtr ptr = getElement(id);
	if (ptr == nullptr) return false;

	ElemPtr elem {getElement(ptr->FirstChildElement(), name)};
	if (elem == nullptr) {
		return false;
	}

	return true;

}
