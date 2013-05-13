/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#ifndef OBJECTINTERFACE_H
#define OBJECTINTERFACE_H

#include "glm.h"

namespace ace {

class ObjectInterface {
protected:
	glm::vec3 m_pos;
	glm::mat4 m_transformation;

public:
	void scale( float s ) {
		m_transformation = glm::scale( m_transformation, glm::vec3( s ) );
	};

	void scale( float x, float y, float z ) {
		m_transformation = glm::scale( m_transformation, glm::vec3( x, y, z ) );
	};

	void rotate( float angle, float x, float y, float z ) {
		angle = angle / 180.0 * 3.14159265358;
		m_transformation = glm::rotate( m_transformation, angle, glm::vec3( x, y, z ) );
	};

	void translate( float x, float y, float z ) {
		m_pos += glm::vec3( x, y, z );
		m_transformation = glm::translate( m_transformation, glm::vec3( x, y, z ) );
	};

	void setPosition( float x, float y, float z ) {
		m_transformation = glm::translate( m_transformation, glm::vec3( x - m_pos.x, y - m_pos.y, z - m_pos.z ) );
		m_pos = glm::vec3( x, y, z );
	}

	inline glm::mat4& getTrafo() { return m_transformation; };
	inline glm::vec3& getPosition() { return m_pos; }
};

};

#endif // OBJECTINTERFACE_H