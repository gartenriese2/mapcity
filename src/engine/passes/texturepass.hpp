#ifndef _TEXTUREPASS_
#define _TEXTUREPASS_

#include "pass.hpp"

#include "../gl/vbo.hpp"
#include "../gl/ibo.hpp"
#include "../gl/vao.hpp"
#include "../gl/texture.hpp"

class TexturePass : public Pass {

 	public:

 		TexturePass(gl::Texture &);
 		~TexturePass() {}

 		void draw();

 	private:

 		gl::VAO m_vertexArray;
 		std::shared_ptr<gl::VBO> m_vertexBufferPtr;
 		std::shared_ptr<gl::IBO> m_indexBufferPtr;
 		gl::Texture & m_tex;

};

#endif // _TEXTUREPASS_