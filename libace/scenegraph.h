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

namespace ace {

class Scenegraph {
private:
    std::vector<Mesh*> m_scenegraph;
public:
    Scenegraph();
    ~Scenegraph();

    void add( Mesh *m );
    std::vector<Mesh*>& getObjects();
};

}

#endif // SCENEGRAPH_H