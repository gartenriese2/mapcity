/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef ERROR_H
#define ERROR_H

#include "stl.h"

namespace ace {

class Error {
private:
	std::string m_error;
public:
	Error();
	~Error();
	void setError( std::string );
	std::string getError();
	bool isError();
	void print();
};

// global object
extern Error g_AceLog;

}

#endif // ERROR_H