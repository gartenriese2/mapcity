#include "database.hpp"

#include "../../engine/debug.hpp"

Database::Database(const std::string & file) {

	if (m_doc.LoadFile(file.c_str()) != 0) {
		m_doc.PrintError();
		return;
	}

}
