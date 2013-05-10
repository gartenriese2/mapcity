/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#ifndef OBJECT_H
#define OBJECT_H

#include "ogl.h"
#include "stl.h"
#include "glm.h"

// Libace
#include "error.h"
// #include "assimpmesh.h"
#include "mesh.h"

namespace ace {

class Object : public Mesh {//, public AssimpMesh {
public:
	Object();
	Object( const std::string& filename );
	bool loadObj( const std::string& filename );
	~Object();
};

}

#endif // OBJECT_H