/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "error.h"

namespace ace {

Error::Error() {
	m_error = "";
}

Error::~Error() {

}

void Error::setError( std::string msg ){
	m_error = msg;
	print();
	m_error = "";
}

std::string Error::getError(){
	return m_error;
}

bool Error::isError() {
	return m_error.length() > 0 ? true : false;
}

void Error::checkGLError( std::string hint ) {
	GLenum errCode;
	std::string errString;

	if ( ( errCode = glGetError() ) != GL_NO_ERROR ) {
    	errString = ( const char * )gluErrorString( errCode );
    	setError( hint + errString );
	}
}

void Error::print(){
	std::cerr << "[ACE-LOG] --" << m_error << std::endl;
}

// global object
Error g_AceLog;

}
