#pragma once


#include <GL/glew.h>
#include <vector>
#include <VertexBuffer.hpp>

namespace Pix{
    class VertexArray{
        private:
            GLuint m_VAO;
            std::vector<VertexBuffer *> m_VertexBuffers;
        public:
            VertexArray();
            ~VertexArray();

            void add(VertexBuffer *buffer, GLuint index);
            void bind() const;
            void unbind() const;
    };
}
