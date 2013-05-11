/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "ogl.h"
#include "stl.h"

// Libace
#include "mesh.h"
#include "light.h"

namespace ace {

class Scenegraph {
private:
    std::vector<Mesh*>  m_scenegraph;
    std::vector<Light*> m_lightgraph;
public:
    Scenegraph();
    ~Scenegraph();
    void add( Mesh *m );
    void add( Light *l );
    std::vector<Light*>& getLights();
    std::vector<Mesh*>& getObjects();
};

}

#endif // SCENEGRAPH_H