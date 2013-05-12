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
    m_intensity = intensity;
    m_radius    = radius;

    m_pos = glm::vec3( 0, 0, 0 );
    setPosition( 0, 0, 0 );

    Mesh::makeQuad();
}

Light::~Light() {

}

void Light::setPosition( float x, float y, float z ) {
	translate( x - m_pos.x, y - m_pos.y, z - m_pos.z );
	m_pos = glm::vec3( x, y, z );
}

glm::vec3& Light::getPosition() {
	return m_pos;
}


}
