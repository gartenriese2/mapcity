#ifndef _SHADERSTORAGEBUFFER_
#define _SHADERSTORAGEBUFFER_

#include "glincludes.hpp"

#include <vector>

class ShaderStorageBuffer {

	public:

		ShaderStorageBuffer();
		~ShaderStorageBuffer();

		void bindTo(unsigned int);

		template <class T>
		void addData(std::vector<T> & data, unsigned int count, GLenum usage = GL_STATIC_DRAW) {
			
			glNamedBufferData(m_name, count * sizeof(T), NULL, usage);
			GLbitfield bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
			T * ld = (T *) glMapNamedBufferRange(m_name, 0, static_cast<GLsizeiptr>(count * sizeof(T)), bufMask);
			for (unsigned int i = 0; i < count; ++i) {
				ld[i] = data[i];
			}
			glUnmapNamedBuffer(m_name);

		}

	private:

		GLuint m_name;

};

#endif // _SHADERSTORAGEBUFFER_