/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#include "light.h"

namespace ace {

Light::Light( float red, float green, float blue, float intensity, float radius ) {
    m_col = glm::vec3( red, green, blue );
    m_pos = glm::vec3( -3, 3, 0 );
    m_intensity = intensity;
    m_radius    = radius;
}


Light::~Light() {

}

}
