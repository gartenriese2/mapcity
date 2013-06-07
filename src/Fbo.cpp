#include "Fbo.hpp"

Fbo::Fbo() {
    m_fbo = 0;
    m_colorAttachments = 0;
}

Fbo::~Fbo() {
    glDeleteFramebuffers(1, &m_fbo);
}

void Fbo::bind() {
    if (!m_fbo) {
        glGenFramebuffers(1, &m_fbo);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Fbo::error() {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "fbo error!\n";
    }
}

void Fbo::createDepthTexture(GLuint& depthTexture, const int width, const int height) {
    
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

}

void Fbo::createColorTexture(GLuint& occlusionTexture, const GLenum format, const int width, const int height) {
    
    glGenTextures(1, &occlusionTexture);
    glBindTexture(GL_TEXTURE_2D, occlusionTexture);

    //glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB16F, width, height); // GLEW too old?
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_colorAttachments++, GL_TEXTURE_2D, occlusionTexture, 0);

}

void Fbo::createDepthRenderBuffer(GLuint& depthrenderbuffer, const int width, const int height) {
    
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

}