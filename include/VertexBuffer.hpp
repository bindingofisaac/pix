#pragma once

#include<OpenGL.hpp>

namespace Pix{
    class VertexBuffer{
        private:
            GLuint m_VBO;
            GLuint m_ComponentCount;
        public:
            VertexBuffer(GLfloat *data, GLsizei count, GLuint componentCount);
            ~VertexBuffer();

            void bind() const;
            void unbind() const;

            inline GLuint getComponentCount() const { return m_ComponentCount; }
    };
}
