#ifndef _DATABASE_
#define _DATABASE_

#include "tinyxml2.h"

#include <string>
#include <memory>

using Elem = tinyxml2::XMLElement;
using ElemPtr = Elem *;

class Database {
	
	public:

		Database(const std::string &);

		bool idExists(const unsigned int) const;
		unsigned int getID(const std::string &) const;

		bool hasElement(unsigned int, const std::string &) const;

		template<typename T>
		T getValue(unsigned int, const std::string &) const;

	protected:

		ElemPtr getElement(ElemPtr, const std::string &) const;
		ElemPtr getElement(unsigned int) const;

		std::shared_ptr<tinyxml2::XMLDocument> m_doc;
		ElemPtr m_root;

};

#endif // _DATABASE_
