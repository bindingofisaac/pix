#include <VertexArray.hpp>

namespace Pix{
    VertexArray::VertexArray(){
        glGenVertexArrays(1, &m_VAO);
    }

    VertexArray::~VertexArray(){
        for(int i=0; i < m_VertexBuffers.size(); i++) delete m_VertexBuffers[i];
        glDeleteVertexArrays(1, &m_VAO);
    }

    void VertexArray::add(VertexBuffer *buffer, GLuint index){
        bind();
        buffer->bind();
        
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

        buffer->unbind();
        unbind();

        m_VertexBuffers.push_back(buffer);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_VAO);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }
}
