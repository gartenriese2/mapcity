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
    int ret = glfwReadImage( filename.c_str(), &m_img, 0 );

    m_rgb_type = m_img.Format;
    m_format   = GL_UNSIGNED_BYTE;
    m_width    = m_img.Width;
    m_height   = m_img.Height;
    m_bpp      = m_img.BytesPerPixel;
    m_data     = m_img.Data;

    return ret == GL_TRUE;
}

}

