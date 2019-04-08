#pragma once

#include <GL/glew.h>

namespace sge { namespace graphics {

	class Buffer {
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

		void bind() const;
		void unbind() const;
 
		inline GLuint getComponentCount() { return m_ComponentCount; }
	};

} }