#include "database.hpp"

#include "../../engine/debug.hpp"

#include <functional>
#include <type_traits>

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
	while ((elem = elem->NextSiblingElement()) != nullptr) {

		if (elem->QueryAttribute("id", &idTmp) == tinyxml2::XML_NO_ERROR) {

			if (id == idTmp) return true;

		}

	}

	return false;

}

unsigned int Database::getID(const std::string & name) const {

	ElemPtr elem {m_root->FirstChildElement()};
	if (elem == nullptr) {
		Debug::log("No elements found in database!");
		return 0u;
	}

	unsigned int id {};

	ElemPtr nameElem {getElement(elem, "name")};
	if (nameElem != nullptr) {
		if (strcmp(nameElem->GetText(), name.c_str()) == 0) {
			if (elem->QueryAttribute("id", &id) == tinyxml2::XML_NO_ERROR) {
				return id;
			} else {
				return 0u;
			}
		}
	}
	
	while ((elem = elem->NextSiblingElement()) != nullptr) {

		nameElem = getElement(elem, "name");
		if (nameElem != nullptr) {
			if (strcmp(nameElem->GetText(), name.c_str()) == 0) {
				if (elem->QueryAttribute("id", &id) == tinyxml2::XML_NO_ERROR) {
					return id;
				} else {
					return 0u;
				}
			}
		}

	}

	return 0u;

}

ElemPtr Database::getElement(unsigned int id) const {

	if (!idExists(id)) return nullptr;

	ElemPtr elem {m_root->FirstChildElement()};
	unsigned int idTmp {0};

	while (elem != nullptr) {

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

	while (ptr != nullptr) {

		if (std::strcmp(ptr->Name(), name.c_str()) == 0) {
			return ptr;
		}

		ptr = ptr->NextSiblingElement();

	}

	return nullptr;

}

int query(ElemPtr elem, int & val) {
	return elem->QueryIntText(&val);
}
int query(ElemPtr elem, unsigned int & val) {
	return elem->QueryUnsignedText(&val);
}
int query(ElemPtr elem, float & val) {
	return elem->QueryFloatText(&val);
}
int query(ElemPtr elem, double & val) {
	return elem->QueryDoubleText(&val);
}
int query(ElemPtr elem, bool & val) {
	return elem->QueryBoolText(&val);
}

template<typename T>
T Database::getValue(unsigned int id, const std::string & name) const {

	static_assert(std::is_same<T, int>::value ||
				  std::is_same<T, unsigned int>::value ||
				  std::is_same<T, float>::value ||
				  std::is_same<T, double>::value ||
				  std::is_same<T, bool>::value,
				  "Type not allowed");

	ElemPtr ptr = getElement(id);
	if (ptr == nullptr) return 0;

	T ret {};
	
	ElemPtr elem {getElement(ptr->FirstChildElement(), name)};
	if (elem == nullptr) {
		Debug::log("No Element " + name + " found");
		return ret;
	}

	if (query(elem, ret) == tinyxml2::XML_NO_ERROR) {
		return ret;
	}

	return {};

}

template int Database::getValue<int>(unsigned int, const std::string &) const;
template unsigned int Database::getValue<unsigned int>(unsigned int, const std::string &) const;
template float Database::getValue<float>(unsigned int, const std::string &) const;
template double Database::getValue<double>(unsigned int, const std::string &) const;
template bool Database::getValue<bool>(unsigned int, const std::string &) const;


bool Database::hasElement(unsigned int id, const std::string & name) const {

	ElemPtr ptr = getElement(id);
	if (ptr == nullptr) return false;

	ElemPtr elem {getElement(ptr->FirstChildElement(), name)};
	if (elem == nullptr) {
		return false;
	}

	return true;

}
