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

void Scenegraph::add( Light *l ) {
    m_lightgraph.push_back( l );
}

std::vector<Light*>& Scenegraph::getLights() {
    return m_lightgraph;
}

std::vector<Mesh*>& Scenegraph::getObjects() {
    return m_scenegraph;
}

}
