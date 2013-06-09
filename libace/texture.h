/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include "ogl.h"
#include "stl.h"
#ifdef __linux__
    #include <cstring>
#endif

// Libace
#include "error.h"

namespace ace {

class Texture {
private:
    GLuint   m_id;
    GLuint   m_width;
    GLuint   m_height;
    GLubyte *m_data;
    GLuint   m_bpp;
    GLuint   m_rgb_type;
    GLenum   m_format;
    GLFWimage m_img;

    // TGA stuff
    bool loadTGA( std::string );
    void init();
public:
    Texture();
    Texture( std::string );
    Texture( GLuint, GLuint ); 
    Texture( GLuint, GLuint, GLuint ); // GL_RGBA etc.
    Texture( GLuint, GLuint, GLuint, GLenum ); // GL_FLOAT etc.
    ~Texture();
    void bind();
    void unbind();
    inline GLuint getId() { return m_id; };
};

}

#endif // TEXTURE_H