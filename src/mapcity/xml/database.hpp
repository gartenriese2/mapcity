#ifndef _DATABASE_
#define _DATABASE_

#include "tinyxml2.h"

#include <string>

class Database {
	
	public:

		Database(const std::string &);

	protected:

		tinyxml2::XMLDocument m_doc;

};

#endif // _DATABASE_
