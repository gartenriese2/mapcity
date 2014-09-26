#ifndef FBO_H
#define FBO_H

#include "glincludes.hpp"
#include <iostream>

class Fbo {
    
    public:
        
        Fbo();
        ~Fbo();

        void bind();
        void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
        void error() const;

        void createDepthTexture(GLuint & , const int, const int);
        void createColorTexture(GLuint &, const GLint, const int, const int);
        void createDepthRenderBuffer(GLuint &, const int, const int);

    private:
        
        GLuint m_fbo;
        unsigned int m_colorAttachments;

};

#endif