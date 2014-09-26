#include "texturepass.hpp"

#include "../camera.hpp"
#include "../objects/objectinterface.hpp"
#include "../debug.hpp"

TexturePass::TexturePass(gl::Texture & tex)
  : m_vertexBufferPtr{new gl::VBO(3)},
  	m_indexBufferPtr{new gl::IBO()},
  	m_tex{tex}
{

	Shader vert {k_dir + "ssq.vert"};
	Shader frag {k_dir + "texture.frag"};
	m_program.attachShader(vert);
	m_program.attachShader(frag);

	m_vertexBufferPtr->insertData({
		-1.f, -1.f, 0.f,
	   	1.f, -1.f, 0.f,
	   	1.f, 1.f, 0.f,
	   	-1.f, 1.f, 0.f
	});
	m_vertexArray.attachVBO(*m_vertexBufferPtr, 0, 0);

	m_indexBufferPtr->insertData({
		0, 1, 2,
		2, 3, 0
	});
	m_vertexArray.attachIBO(*m_indexBufferPtr);

}

void TexturePass::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	m_program.use();

	m_program["tex"] = {0};
	glBindTextureUnit(0, m_tex);

	m_vertexArray.draw(static_cast<GLsizei>(m_indexBufferPtr->getSize()));

}
