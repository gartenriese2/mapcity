/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#include "light.h"

namespace ace {

Light::Light() {
    m_col_diffuse           = glm::vec4( 0.7, 0.7, 0.7, 1.0 );
    m_col_specular          = glm::vec4( 0.7, 0.7, 0.7, 1.0 );
    m_col_ambient           = glm::vec4( 0.5, 0.5, 0.5, 1.0 );

    m_pos = glm::vec3( -3, 3, 0 );
}


Light::~Light() {

}

}
