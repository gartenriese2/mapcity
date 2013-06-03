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
#include "texture.h"

namespace ace {

class Mesh : public ObjectInterface {
protected:
	GLuint vao_vert;
	GLuint vao_uv;
	GLuint vao_vn;

	GLuint vert_buffer;
	GLuint uv_buffer;
	GLuint vn_buffer;

	Texture *m_texture;

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

	inline GLuint getVertexBuffer() { return vert_buffer; }
	inline GLuint getTextureBuffer() { return uv_buffer; }
	inline GLuint getNormalBuffer() { return vn_buffer; }

	inline bool hasVertices() { return m_vt.size() > 0; }
	inline bool hasTextureCoords() { return m_uv.size() > 0; }
	inline bool hasNormals() { return m_vn.size() > 0; }

	inline unsigned int getVerticesIndex() { return vert_index; }
	inline unsigned int getVerticesCount() { return m_idx.size(); }

	inline unsigned int getTextureId() { return m_texture->getId(); }

	void makeCube();
	void makeQuad();
};

}

#endif // MESH_H