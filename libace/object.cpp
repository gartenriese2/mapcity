/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "object.h"

namespace ace {

Object::Object() {
	Mesh::makeCube();
}

Object::Object( const std::string& filename ) {
	if( !loadObj( filename ) ) {
		g_AceLog.setError( "Object loading failed." );
	}
}

Object::~Object() {

}

bool Object::loadObj( const std::string& filename ) {
	std::ifstream f( filename.c_str(), std::ios::in );
	std::string line;
	int linecount = 0;

	if( !f.good() ) {
		g_AceLog.setError( "Object file could not be found." );
		return false;
	}

	// "t_" is for temporary
	std::vector<glm::vec3> t_vt; // normals
	std::vector<glm::vec3> t_vn; // normals
	std::vector<glm::vec2> t_uv; // vertices

	std::vector<unsigned int> t_vt_idx; // vertices
	std::vector<unsigned int> t_vn_idx; // vertices
	std::vector<unsigned int> t_uv_idx; // vertices

	while( !f.eof() ) {
		linecount++;

		// check line beginning for vt, vn, uv
		std::string line_beginning;
		std::getline( f, line );
		line_beginning = line.substr( 0, line.find( " " ) );

		// vertices 3 floats: vt
		if( line_beginning == "v" ) {
			glm::vec3 vert;
			line[ 0 ] = ' '; // kill v
			sscanf( line.c_str(), "%f %f %f ", &vert.x, &vert.y, &vert.z );
			// cout << "-- reading v " << vert << endl;
			t_vt.push_back( vert );
		} 
		// vertices 2 floats: uv
		else if( line_beginning == "vt" ) {
			glm::vec2 vert;
			line[ 0 ] = ' '; 
			line[ 1 ] = ' '; 
			sscanf( line.c_str(), "%f %f ", &vert.x, &vert.y );
			// cout << "-- reading vt " << vert << endl;
			t_uv.push_back( vert );
		} 
		// vertices 3 floats: normals
		else if( line_beginning == "vn" ) {
			glm::vec3 vert;
			line[ 0 ] = ' '; 
			line[ 1 ] = ' '; 
			sscanf( line.c_str(), "%f %f %f ", &vert.x, &vert.y, &vert.z );
			// cout << "-- reading vn " << vert << endl;
			t_vn.push_back( vert );
		} 
		// faces
		else if( line_beginning == "f" ) {
			// cout << "-- reading f" << endl;
			unsigned int vt[3], uv[3], vn[3];
			line[ 0 ] = ' '; 

			int ret = sscanf( line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d ", 
							  &vt[0], &uv[0], &vn[0], 
							  &vt[1], &uv[1], &vn[1], 
							  &vt[2], &uv[2], &vn[2] );
			if( ret != 9 ) {
				// try another one
				ret = sscanf( line.c_str(), "%d %d %d ", &vt[0], &vt[0], &vt[0] );
				if( ret == 3 ) {
					t_vt_idx.push_back( vt[0] - 1 );
					t_vt_idx.push_back( vt[1] - 1 );
					t_vt_idx.push_back( vt[2] - 1 );
					continue;
				} 
				else {
					std::stringstream error;
					error << "Warning: faces not in format x/x/x in line " << linecount; 
					g_AceLog.setError( error.str() );
					continue;					
				}
			}

			t_vt_idx.push_back( vt[0] - 1 );
			t_vt_idx.push_back( vt[1] - 1 );
			t_vt_idx.push_back( vt[2] - 1 );

			t_uv_idx.push_back( uv[0] - 1 );
			t_uv_idx.push_back( uv[1] - 1 );
			t_uv_idx.push_back( uv[2] - 1 );

			t_vn_idx.push_back( vn[0] - 1 );
			t_vn_idx.push_back( vn[1] - 1 );
			t_vn_idx.push_back( vn[2] - 1 );
		} 
		else {
			// cout << "-- reading comment" << endl;
		}
	} 

	// reorder stuff
	// for( int i = 0; i < t_vt.size(); ++i ) {
	// 	m_vt.push_back( glm::vec3( 0, 0, 0 ) );
	// 	m_vn.push_back( glm::vec3( 0, 0, 0 ) );
	// 	m_uv.push_back( glm::vec2( 0, 0 ) );
	// }

	// std::vector<int> known_idx;
	// for( int i = 0; i < m_vt_idx.size(); ++i ) {
	// 	int idx = m_vt_idx.at( i );

	// 	// check if this index is already present
	// 	if( std::find( known_idx.begin(), known_idx.end(), idx ) != known_idx.end() ) {
	// 		std::cout << "Index problem " << idx << std::endl;
	// 		// check if the triple is the same
	// 		if( m_vn.at( idx ) == t_vn.at( m_vn_idx.at( i ) ) && 
	// 			m_uv.at( idx ) == t_uv.at( m_uv_idx.at( i ) ) ) {
	// 			// yes its present, so use it instead!
	// 			std::cout << "-- present " << std::endl;				
	// 		}
	// 		else {
	// 			// create a new triple
	// 			std::cout << "-- new one " << std::endl;				
	// 		}
	// 	} else {
	// 		m_vt.at( idx ) = t_vt.at( idx );
	// 		m_vn.at( idx ) = t_vn.at( m_vn_idx.at( i ) );
	// 		m_uv.at( idx ) = t_uv.at( m_uv_idx.at( i ) );

	// 		// mark this index as already processed
	// 		known_idx.push_back( idx );
	// 	}
	// }

	// for( int i = 0; i < m_vt_idx.size(); ++i ) {	
	// 	int idx = m_vt_idx.at( i );
	// 	std::cout << "idx: " << idx << std::endl;
	// 	std::cout << "-- " << m_vt.at( idx ).x << ", " << m_vt.at( idx ).y << ", " << m_vt.at( idx ).z << std::endl;
	// 	std::cout << "-- " << m_uv.at( idx ).x << ", " << m_uv.at( idx ).y << std::endl;
	// 	std::cout << "-- " << m_vn.at( idx ).x << ", " << m_vn.at( idx ).y << ", " << m_vn.at( idx ).z << std::endl;
	// 	std::cout << std::endl;
	// }

	for( unsigned long i = 0; i < t_vt_idx.size(); ++i ) {
		m_idx.push_back( 0 );
	}

	// std::cout << "Vertices: " << std::endl;

	m_vt.clear();
	for( unsigned long i = 0; i < t_vt_idx.size(); ++i ) {
		m_vt.push_back( t_vt.at( t_vt_idx.at( i ) ) );
		m_idx[i] = i;

		// std::cout << m_vt[i].x << ", " << m_vt[i].y << ", " << m_vt[i].z << std::endl;
	}

	// std::cout << "UVs: " << std::endl;

	m_uv.clear();
	for( unsigned long i = 0; i < t_uv_idx.size(); ++i ) {
		m_uv.push_back( t_uv.at( t_uv_idx.at( i ) ) );

		// std::cout << m_uv[i].x << ", " << m_uv[i].y << std::endl;
	}

	// std::cout << "Normals: " << std::endl;

	m_vn.clear();
	for( unsigned long i = 0; i < t_vn_idx.size(); ++i ) {
		m_vn.push_back( t_vn.at( t_vn_idx.at( i ) ) );

		// std::cout << m_vn[i].x << ", " << m_vn[i].y << ", " << m_vn[i].z << std::endl;
	}

	f.close();

	Mesh::update();

	return true;
}

}