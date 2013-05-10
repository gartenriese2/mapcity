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

	float vns[] = {
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,

		-1, 0, 0,
	};

	float uvs[] = {
		0.000059f, 1.0f-0.000004f,
	    0.000103f, 1.0f-0.336048f,
	    0.335973f, 1.0f-0.335903f,
	    1.000023f, 1.0f-0.000013f,
	    0.667979f, 1.0f-0.335851f,
	    0.999958f, 1.0f-0.336064f,
	    0.667979f, 1.0f-0.335851f,
	    0.336024f, 1.0f-0.671877f,
	    0.667969f, 1.0f-0.671889f,
	    1.000023f, 1.0f-0.000013f,
	    0.668104f, 1.0f-0.000013f,
	    0.667979f, 1.0f-0.335851f,
	    0.000059f, 1.0f-0.000004f,
	    0.335973f, 1.0f-0.335903f,
	    0.336098f, 1.0f-0.000071f,
	    0.667979f, 1.0f-0.335851f,
	    0.335973f, 1.0f-0.335903f,
	    0.336024f, 1.0f-0.671877f,
	    1.000004f, 1.0f-0.671847f,
	    0.999958f, 1.0f-0.336064f,
	    0.667979f, 1.0f-0.335851f,
	    0.668104f, 1.0f-0.000013f,
	    0.335973f, 1.0f-0.335903f,
	    0.667979f, 1.0f-0.335851f,
	    0.335973f, 1.0f-0.335903f,
	    0.668104f, 1.0f-0.000013f,
	    0.336098f, 1.0f-0.000071f,
	    0.000103f, 1.0f-0.336048f,
	    0.000004f, 1.0f-0.671870f,
	    0.336024f, 1.0f-0.671877f,
	    0.000103f, 1.0f-0.336048f,
	    0.336024f, 1.0f-0.671877f,
	    0.335973f, 1.0f-0.335903f,
	    0.667969f, 1.0f-0.671889f,
	    1.000004f, 1.0f-0.671847f,
	    0.667979f, 1.0f-0.335851f
	};

	float verts[] = {
	    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	    -1.0f,-1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f, // triangle 1 : end
	    1.0f, 1.0f,-1.0f, // triangle 2 : begin
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f, // triangle 2 : end

	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,

	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,

	    -1.0f, 1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,

	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,
	    
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f
	};

	for( int i = 0; i < num; ++i ) {
		glm::vec2 uv( uvs[2*i], uvs[2*i+1] );
		m_uv.push_back( uv );
	}

	for( int i = 0; i < num; ++i ) {
		glm::vec3 vec( verts[3*i], verts[3*i+1], verts[3*i+2] );

		m_idx.push_back( i );
		m_vt.push_back( vec );
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
		m_uv.push_back( uv );
	}

	for( int i = 0; i < num; ++i ) {
		glm::vec3 vec( verts[3*i], verts[3*i+1], verts[3*i+2] );

		m_idx.push_back( i );
		m_vt.push_back( vec );
	}

	for( int i = 0; i < num; ++i ) {
		glm::vec3 vec( vns[3*i], vns[3*i+1], vns[3*i+2] );
		m_vn.push_back( vec );
	}

	update();
}

}