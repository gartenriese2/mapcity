#include "database.hpp"

#include "../../engine/debug.hpp"

Database::Database(const std::string & file)
  : m_doc(new tinyxml2::XMLDocument())
{

	if (m_doc->LoadFile(file.c_str()) != 0) {
		m_doc->PrintError();
		return;
	}

}

bool Database::idExists(const unsigned int id) const {

	ElemPtr elem {m_root->FirstChildElement()};
	if (elem == nullptr) {
		Debug::log("No elements found in database!");
		return false;
	}

	unsigned int idTmp {0};
	if (elem->QueryAttribute("id", &idTmp) == tinyxml2::XML_NO_ERROR) {
		if (id == idTmp) return true;
	}
	while((elem = elem->NextSiblingElement()) != nullptr) {

		if (elem->QueryAttribute("id", &idTmp) == tinyxml2::XML_NO_ERROR) {

			if (id == idTmp) return true;

		}

	}

	return false;

}

ElemPtr Database::getElement(unsigned int id) const {

	if (!idExists(id)) return nullptr;

	ElemPtr elem {m_root->FirstChildElement()};
	unsigned int idTmp {0};

	while(elem != nullptr) {

		if (elem->QueryAttribute("id", &idTmp) == tinyxml2::XML_NO_ERROR) {
			if (id == idTmp) {
				return elem;
			}
		}

		elem = elem->NextSiblingElement();

	}

	return nullptr;

}

ElemPtr Database::getElement(ElemPtr ptr, const std::string & name) const {

	while(ptr != nullptr) {

		if (std::strcmp(ptr->Name(), name.c_str()) == 0) {
			return ptr;
		}

		ptr = ptr->NextSiblingElement();

	}

	return nullptr;

}
