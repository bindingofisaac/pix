#pragma once

#include <OpenGL.hpp>

namespace Pix{
    class IndexBuffer{
        private:
            GLuint m_IBO;
            GLuint m_Count;
        public:
            IndexBuffer(GLushort *data, GLsizei count);
            ~IndexBuffer();

            void bind() const;
            void unbind() const;

            inline GLuint getCount() const { return m_Count; }
    };
}
