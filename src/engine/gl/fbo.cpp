#include "fbo.hpp"

#include "texture.hpp"
#include "../debug.hpp"

namespace gl {

FBO::FBO()
  : gl::Object(GL_FRAMEBUFFER),
  	m_colorAttachments{0}
{

	glCreateFramebuffers(1, &m_name);

}

FBO::~FBO() {

	glDeleteFramebuffers(1, &m_name);

}

bool FBO::isValid() const {
	return glIsFramebuffer(m_name);
}

void FBO::bind(GLenum target) const {

	glBindFramebuffer(target, m_name);

}

void FBO::unbind(GLenum target) const {

	glBindFramebuffer(target, 0);

}

void FBO::attachColorTexture(const gl::Texture & tex, GLenum target) {

	if (isValid()) {
		
		glNamedFramebufferTexture(m_name, GL_COLOR_ATTACHMENT0 + m_colorAttachments++, tex, 0);
		checkError(target);

	}

}

void FBO::attachDepthTexture(const gl::Texture & tex, GLenum target) {

	if (isValid()) {
		
		glNamedFramebufferTexture(m_name, GL_DEPTH_ATTACHMENT, tex, 0);
		checkError(target);

	}

}

void FBO::checkError(GLenum target) const {

	GLenum err = glCheckNamedFramebufferStatus(m_name, target);
	if (err != GL_FRAMEBUFFER_COMPLETE) {
		switch(err) {
			case GL_FRAMEBUFFER_UNDEFINED:
				Debug::log("undefined fbo");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				Debug::log("incomplete attachment");
				break;
			default:
				Debug::log("some fbo error");
		};
	}

}

void FBO::blit(GLenum src, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
	GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {

	if (isValid()) {
	
		glNamedFramebufferReadBuffer(m_name, src);
		glBlitNamedFramebuffer(m_name, 0, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);

	}

}

} // namespace gl
