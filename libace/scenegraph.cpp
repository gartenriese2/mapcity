/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#include "scenegraph.h"

namespace ace {

Scenegraph::Scenegraph() {

}

Scenegraph::~Scenegraph() {
    
}

void Scenegraph::add( Mesh *m ) {
    m_scenegraph.push_back( m );
}

std::vector<Mesh*>& Scenegraph::getObjects() {
    return m_scenegraph;
}

}
