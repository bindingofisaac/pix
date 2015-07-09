#include <VertexBuffer.hpp>

namespace Pix{
    VertexBuffer::VertexBuffer(GLfloat *data, GLsizei count, GLuint componentCount) : m_ComponentCount(componentCount){
        glGenBuffers(1, &m_VBO);
        bind();
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
        unbind();
    }

    VertexBuffer::~VertexBuffer(){
        glDeleteBuffers(1, &m_VBO);
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
