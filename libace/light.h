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
#include "mesh.h"

namespace ace {

class Light : public Mesh {
private:
	glm::vec3 m_pos;
	glm::vec3 m_col;

	float m_intensity;
	float m_radius;

public:
    Light( float red, float green, float blue, float intensity, float radius );
    ~Light();

    void setPosition( float x, float y, float z );
    glm::vec3& getPosition();
    inline glm::vec3& getColor() { return m_col; }
    inline float getRadius() { return m_radius; }
    inline float getIntensity() { return m_intensity; }
};

}

#endif // LIGHT_H