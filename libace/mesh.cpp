/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "mesh.h"

namespace ace {

Mesh::Mesh() {
	m_texture = new Texture();
}

void Mesh::update() {
	glGenBuffers( 1, &vert_buffer );
	glBindBuffer( GL_ARRAY_BUFFER, vert_buffer );
	glBufferData( GL_ARRAY_BUFFER, m_vt.size() * sizeof( glm::vec3 ), &m_vt[0], GL_STATIC_DRAW );

	glGenBuffers( 1, &vn_buffer );
	glBindBuffer( GL_ARRAY_BUFFER, vn_buffer );
	glBufferData( GL_ARRAY_BUFFER, m_vn.size() * sizeof( glm::vec3 ), &m_vn[0], GL_STATIC_DRAW );

	glGenBuffers( 1, &uv_buffer );
	glBindBuffer( GL_ARRAY_BUFFER, uv_buffer );
	glBufferData( GL_ARRAY_BUFFER, m_uv.size() * sizeof( glm::vec2 ), &m_uv[0], GL_STATIC_DRAW );

	glGenBuffers( 1, &vert_index );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vert_index );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_idx.size() * sizeof( unsigned int ), &m_idx[0], GL_STATIC_DRAW );
}

Mesh::~Mesh() {
	glDeleteBuffers( 1, &vert_buffer );
	glDeleteBuffers( 1, &uv_buffer );
	glDeleteBuffers( 1, &vn_buffer );
	glDeleteBuffers( 1, &vert_index );
}

void Mesh::draw() {
	// verts
	if( m_vt.size() > 0 ) {
		glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, vert_buffer );
		glVertexAttribPointer(  cfg::ACE_ATTRIB_VERT, 
								3, // glm::vec3
								GL_FLOAT,
								GL_FALSE,
								0,
								0 );
	}

	// uvs
	if( m_uv.size() > 0 ) {
		glEnableVertexAttribArray( 1 );
		glBindBuffer( GL_ARRAY_BUFFER, uv_buffer );
		glVertexAttribPointer(  cfg::ACE_ATTRIB_UV, 
								2, // glm::vec2
								GL_FLOAT,
								GL_FALSE,
								0,
								0 );
	}

	// normals
	if( m_vn.size() > 0 ) {
		glEnableVertexAttribArray( 2 );
		glBindBuffer( GL_ARRAY_BUFFER, vn_buffer );
		glVertexAttribPointer(  cfg::ACE_ATTRIB_NORM, 
								3, // glm::vec3
								GL_FLOAT,
								GL_FALSE,
								0,
								0 );
	}

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vert_index );
	glDrawElements( GL_TRIANGLES, m_idx.size(), GL_UNSIGNED_INT, 0 );
		

	// clean up
	glDisableVertexAttribArray( 2 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 0 );
}

void Mesh::makeCube() {
	unsigned int num = 36;

	float verts[] = {
		1, -1, -1,
		1, -1, 1,
		-1, -1, 1,
		1, -1, -1,
		-1, -1, 1,
		-1, -1, -1,
		1, 1, -0.999999,
		-1, 1, -1,
		-1, 1, 1,
		1, 1, -0.999999,
		-1, 1, 1,
		0.999999, 1, 1,
		1, -1, -1,
		1, 1, -0.999999,
		0.999999, 1, 1,
		1, -1, -1,
		0.999999, 1, 1,
		1, -1, 1,
		1, -1, 1,
		0.999999, 1, 1,
		-1, 1, 1,
		1, -1, 1,
		-1, 1, 1,
		-1, -1, 1,
		-1, -1, 1,
		-1, 1, 1,
		-1, 1, -1,
		-1, -1, 1,
		-1, 1, -1,
		-1, -1, -1,
		1, 1, -0.999999,
		1, -1, -1,
		-1, -1, -1,
		1, 1, -0.999999,
		-1, -1, -1,
		-1, 1, -1
	};

	float vns[] = {
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		-0, -0, 1,
		-0, -0, 1,
		-0, -0, 1,
		-0, -0, 1,
		-0, -0, 1,
		-0, -0, 1,
		-1, -0, -0,
		-1, -0, -0,
		-1, -0, -0,
		-1, -0, -0,
		-1, -0, -0,
		-1, -0, -0,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1
	};

	float uvs[] = {
		0, 0.500086,
		0.332314, 0.498587,
		0.333333, 0.987448,
		0, 0.500086,
		0.333333, 0.987448,
		0.00102, 0.988948,
		1, 0.009725,
		0.998981, 0.498586,
		0.666667, 0.497087,
		1, 0.009725,
		0.666667, 0.497087,
		0.667686, 0.008225,
		0.998981, 0.498587,
		1, 0.987448,
		0.667686, 0.988948,
		0.998981, 0.498587,
		0.667686, 0.988948,
		0.666667, 0.500086,
		0.334353, 0.988948,
		0.333333, 0.500086,
		0.665647, 0.498587,
		0.334353, 0.988948,
		0.665647, 0.498587,
		0.666667, 0.987448,
		0.333333, 0.497087,
		0.00102, 0.498587,
		0, 0.009725,
		0.333333, 0.497087,
		0, 0.009725,
		0.332314, 0.008225,
		0.333333, 0.009725,
		0.665647, 0.008225,
		0.666667, 0.497087,
		0.333333, 0.009725,
		0.666667, 0.497087,
		0.334353, 0.498587
	};

	for( int i = 0; i < num; ++i ) {
		glm::vec3 vt( verts[3*i], verts[3*i+1], verts[3*i+2] );
		glm::vec2 uv( uvs[2*i], uvs[2*i+1] );
		glm::vec3 vn( vns[3*i], vns[3*i+1], vns[3*i+2] );

		m_idx.push_back( i );
		m_vt.push_back( vt );
		m_uv.push_back( uv );
		m_vn.push_back( vn );
	}

	update();
}

void Mesh::makeQuad() {
	unsigned int num = 6;

	float uvs[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,

        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
	};

	float verts[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    float vns[] = {
    	0, 0, 1,
    	0, 0, 1,
    	0, 0, 1,

    	0, 0, 1,
    	0, 0, 1,
    	0, 0, 1
    };

	for( int i = 0; i < num; ++i ) {
		glm::vec2 uv( uvs[2*i], uvs[2*i+1] );
		glm::vec3 vt( verts[3*i], verts[3*i+1], verts[3*i+2] );
		glm::vec3 vn( vns[3*i], vns[3*i+1], vns[3*i+2] );

		m_idx.push_back( i );
		m_vt.push_back( vt );
		m_vn.push_back( vn );
		m_uv.push_back( uv );
	}

	update();
}

}