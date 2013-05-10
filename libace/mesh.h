/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/
#ifndef MESH_H
#define MESH_H

#include "ogl.h"
#include "stl.h"
#include "glm.h"

// Libace
#include "config.h"
#include "objectinterface.h"

namespace ace {

class Mesh : public ObjectInterface {
protected:
	GLuint vert_buffer;
	GLuint uv_buffer;
	GLuint vn_buffer;

	// these vectors contain the data itself
	std::vector<glm::vec2> m_uv; // texture coordinates
	std::vector<glm::vec3> m_vn; // normals
	std::vector<glm::vec3> m_vt; // vertices

	// the index vectors tells us the order of the faces
	GLuint vert_index;
	std::vector<unsigned int> m_idx; // indices

	void update();
public:
	Mesh();
	~Mesh();
	void draw();

	void makeCube();
	void makeQuad();
};

}

#endif // MESH_H