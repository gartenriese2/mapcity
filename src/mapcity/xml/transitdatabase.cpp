#include "transitdatabase.hpp"

#include "tinyxml2.h"
#include "../../engine/debug.hpp"

#include <cstring>

const std::string k_rootName {"transitdatabase"};

TransitDatabase::TransitDatabase(const std::string & file)
  : Database(file)
{

	m_root = m_doc->RootElement();
	if (m_root == nullptr) {
		Debug::log("No root element found in " + file);
		exit(EXIT_FAILURE);
	}
	
	if (std::strcmp(m_root->Name(), "transitdatabase") != 0) {
		Debug::log(file + " is not a valid transitdatabase file"
			+ "(Missing transitdatabase root element");
		exit(EXIT_FAILURE);
	}

}
