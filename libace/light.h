/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef LIGHT_H
#define LIGHT_H

#include "ogl.h"
#include "glm.h"
#include "stl.h"

// Libace

namespace ace {

class Light {
private:
	glm::vec3 m_pos;
	glm::vec3 m_col;

public:
    Light( float red, float green, float blue );
    ~Light();

    inline void setPosition( float x, float y, float z ) { m_pos = glm::vec3( x, y, z ); }
    inline glm::vec3& getPosition() { return m_pos; }
    inline glm::vec3& getColor() { return m_col; }
};

}

#endif // LIGHT_H