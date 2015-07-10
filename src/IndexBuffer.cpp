#include <IndexBuffer.hpp>


namespace Pix{
    IndexBuffer::IndexBuffer(GLushort *data, GLsizei count) : m_Count(count) {
        glGenBuffers(1, &m_IBO);
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
        unbind();
    }

    IndexBuffer::~IndexBuffer(){
        glDeleteBuffers(1, &m_IBO);
    }

    void IndexBuffer::bind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    }

    void IndexBuffer::unbind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
