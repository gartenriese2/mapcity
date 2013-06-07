#ifndef FBO_H
#define FBO_H

#include "ogl.h"
#include <iostream>

class Fbo {
public:
    
    Fbo();
    ~Fbo();

    void bind();
    inline void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
    void error();

    void createDepthTexture(GLuint& , const int, const int);
    void createColorTexture(GLuint&, const GLenum, const int, const int);
    void createLightingTexture(GLuint&, const int, const int);
    void createDepthRenderBuffer(GLuint&, const int, const int);

private:
    
    GLuint m_fbo;
    int m_colorAttachments;

};

#endif