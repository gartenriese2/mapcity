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
		ElemPtr getElement(unsigned int) const;
		ElemPtr getElement(ElemPtr, const std::string &) const;

	protected:

		std::shared_ptr<tinyxml2::XMLDocument> m_doc;
		ElemPtr m_root;

};

#endif // _DATABASE_
