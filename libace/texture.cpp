/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "texture.h"

namespace ace {

Texture::Texture() {
    // 24 - bit tga sample texture
    unsigned char m_sample_tex[] = {
        0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 
        0x04, 0x00, 0x18, 0x00, 0xFF, 0xCF, 0x7C, 
        0xC5, 0x80, 0x07, 0xFF, 0xCF, 0x7C, 0xC5, 
        0x80, 0x07, 0xC5, 0x80, 0x07, 0xFF, 0xCF, 
        0x7C, 0xC5, 0x80, 0x07, 0xFF, 0xCF, 0x7C, 
        0xFF, 0xCF, 0x7C, 0xC5, 0x80, 0x07, 0xFF, 
        0xCF, 0x7C, 0xC5, 0x80, 0x07, 0xC5, 0x80, 
        0x07, 0xFF, 0xCF, 0x7C, 0xC5, 0x80, 0x07, 
        0xFF, 0xCF, 0x7C, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x54, 0x52, 0x55, 
        0x45, 0x56, 0x49, 0x53, 0x49, 0x4F, 0x4E, 
        0x2D, 0x58, 0x46, 0x49, 0x4C, 0x45, 0x2E, 
        0x00
    }; 

    // write
    std::ofstream fp( "sample_tex.tga", std::ios::binary );
    fp.write( ( const char * )m_sample_tex, sizeof( m_sample_tex ) );
    fp.close();

    // load
    if( loadTGA( "sample_tex.tga" ) ) {
        init();
    }
}

Texture::Texture( std::string filename ) {
    if( loadTGA( filename ) ) {

        init();

    }
}

Texture::Texture( GLuint width, GLuint height ) {
    m_width    = width;
    m_height   = height;
    m_rgb_type = GL_RGB;
    m_format   = GL_UNSIGNED_BYTE;
    m_data     = 0;

    init();
} 

Texture::Texture( GLuint width, GLuint height, GLuint type ) {
    m_width    = width;
    m_height   = height;
    m_rgb_type = type; // GL_RGBA, GL_RGB, GL_DEPTH_COMPONENT
    m_format   = GL_UNSIGNED_BYTE;
    m_data     = 0;

    init();
} 

Texture::Texture( GLuint width, GLuint height, GLuint type, GLenum format ) {
    m_width    = width;
    m_height   = height;
    m_rgb_type = type; // GL_RGBA, GL_RGB, GL_DEPTH_COMPONENT
    m_format   = format;
    m_data     = 0;

    init();
} 

void Texture::init() {
    glGenTextures( 1, &m_id );

    bind();

    // this is obviously a bad way... :)
    GLuint type = GL_RGBA;
    if( m_rgb_type == GL_DEPTH_COMPONENT ) type = GL_DEPTH_COMPONENT;
    if( m_rgb_type == GL_RGB ) type = GL_RGB;

    glTexImage2D( GL_TEXTURE_2D, 0, m_rgb_type, m_width, m_height, 0, type, m_format, m_data );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
}

Texture::~Texture() {
    delete[] m_data;
}

void Texture::bind() {
    glActiveTexture( GL_TEXTURE0 + m_id );
    glBindTexture( GL_TEXTURE_2D, m_id );
}

void Texture::unbind() {
    glBindTexture( GL_TEXTURE_2D, 0 );
}

bool Texture::loadTGA( std::string filename ) {
    m_format = GL_UNSIGNED_BYTE;

    std::ifstream file( filename.c_str(), std::ios::binary );
    if( !file.good() ) {
        std::string error = "Could not load texture " + filename;
        g_AceLog.setError( error );
        return false; 
    }

    // check tga header to detect compressed version
    GLubyte cmp_tga[ 12 ]       = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    GLubyte cmp_tga_ucomp[ 12 ] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    GLubyte cmp_tga_compr[ 12 ] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    file.read( reinterpret_cast<char*>( cmp_tga ), sizeof( cmp_tga ) );

    if( memcmp( cmp_tga_ucomp, &cmp_tga, sizeof( cmp_tga ) ) == 0 ) {
        return loadUncompressedTGA( file );
    } 
    else if( memcmp( cmp_tga_compr, &cmp_tga, sizeof( cmp_tga ) ) == 0 ) {
        return loadCompressedTGA( file );
    } 
    else {
        return false;
    }

    return false;
}

bool Texture::loadUncompressedTGA( std::ifstream& file ) {
    char header[ 6 ];
    unsigned int bytespp = 0;
    unsigned int size = 0;

    file.read( header, sizeof( header ) );

    m_width  = header[ 1 ] * 256 + header[ 0 ];
    m_height = header[ 3 ] * 256 + header[ 2 ];
    m_bpp    = header[ 4 ];

    if( m_width < 1 || m_height < 1 || ( m_bpp != 24 && m_bpp != 32 ) ) {
        return false;
    }

    if( m_bpp == 24 ) {
        m_rgb_type = GL_RGB;
    } 
    else if( m_bpp == 32 ) {
        m_rgb_type = GL_RGBA;
    }

    bytespp = m_bpp / 8;
    size    = m_width * m_height * bytespp;
    m_data  = new GLubyte[ size ];

    file.read( reinterpret_cast<char*>( m_data ), size );

    // convert BGR to RGB
    for( int i = 0; i < size; i += bytespp ) {
        m_data[ i ] ^= m_data[ i + 2 ] ^= 
        m_data[ i ] ^= m_data[ i + 2 ];
    }

    file.close();

    // cout << "Uncompressed: " << m_width << " * " << m_height << " * " << m_bpp << endl;
    return true;
}

bool Texture::loadCompressedTGA( std::ifstream& file ) {
    char header[ 6 ];
    unsigned int bytespp    = 0;
    unsigned int size       = 0;
    unsigned int pixelcount = 0;
    int currentpixel        = 0;
    int currentbyte         = 0;
    char *colorbuf          = 0;

    file.read( header, sizeof( header ) );

    m_width  = header[ 1 ] * 256 + header[ 0 ];
    m_height = header[ 3 ] * 256 + header[ 2 ];
    m_bpp    = header[ 4 ];

    if( m_width < 1 || m_height < 1 || ( m_bpp != 24 && m_bpp != 32 ) ) {
        return false;
    }

    if( m_bpp == 24 ) {
        m_rgb_type = GL_RGB;
    } 
    else if( m_bpp == 32 ) {
        m_rgb_type = GL_RGBA;
    }

    bytespp    = m_bpp / 8;
    size       = m_width * m_height * bytespp;
    m_data     = new GLubyte[ size ];
    pixelcount = m_width * m_height;
    colorbuf   = new char[ bytespp ];


    do {
        char chunkheader = 0;
        file.read( &chunkheader, sizeof( chunkheader ) );

        if( chunkheader < 128 ) {
            chunkheader++;

            for( int i = 0; i < chunkheader; ++i ) {
                file.read( colorbuf, sizeof( colorbuf ) );
                
                m_data[ currentbyte ]     = colorbuf[ 2 ];
                m_data[ currentbyte + 1 ] = colorbuf[ 1 ];
                m_data[ currentbyte + 2 ] = colorbuf[ 0 ];

                if( bytespp == 4 ) {
                    m_data[ currentbyte + 3 ] = colorbuf[ 3 ];
                }

                currentbyte += bytespp;
                currentpixel++;
            }
        } else {
            chunkheader -= 127;
            file.read( colorbuf, sizeof( colorbuf ) );

            for( int i = 0; i < chunkheader; ++i ) {
                m_data[ currentbyte ]     = colorbuf[ 2 ];
                m_data[ currentbyte + 1 ] = colorbuf[ 1 ];
                m_data[ currentbyte + 2 ] = colorbuf[ 0 ];

                if( bytespp == 4 ) {
                    m_data[ currentbyte + 3 ] = colorbuf[ 3 ];
                }

                currentbyte += bytespp;
                currentpixel++;
            }
        }
    } while( currentpixel < pixelcount );

    file.close();

    // cout << "Compressed: " << m_width << " * " << m_height << " * " << m_bpp << endl;
    return true;
}

}

