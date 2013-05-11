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

// Libace

namespace ace {

class Light {
private:
	glm::vec3 m_pos;
	float m_radius; 

	glm::vec4 m_col_diffuse;
	glm::vec4 m_col_specular;
	glm::vec4 m_col_ambient;

	float m_intensity_diffuse;
	float m_intensity_specular;
	float m_intensity_ambient;

public:
    Light();
    ~Light();

    inline glm::vec3& getPosition() { return m_pos; }
    inline float getRadius() { return m_radius; }
};

}

#endif // LIGHT_H