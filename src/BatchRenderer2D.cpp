#include <BatchRenderer2D.hpp>

namespace Pix{
    BatchRenderer2D::BatchRenderer2D() : m_IndexCount(0){
        init();
    }

    BatchRenderer2D::~BatchRenderer2D(){
        delete m_IBO;
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void BatchRenderer2D::init(){
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLushort *indices = new GLushort[RENDERER_INDICES_SIZE];

        for(int i=0, offset=0;i<RENDERER_INDICES_SIZE;i+=6, offset += 4){
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
        }

        m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

        glBindVertexArray(0);
    }

    void BatchRenderer2D::begin(){
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_Buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void BatchRenderer2D::submit(const Renderable2D* renderable){
        const glm::vec4 &position = glm::vec4(renderable->getPosition(), 1);
        const glm::vec2 &size     = renderable->getSize();
        const glm::vec4 &color    = renderable->getColor();
        glm::mat4 ts = m_TransformationStack.back();

        m_Buffer->vertex = (ts * position).xyz();
        m_Buffer->color  = color;
        m_Buffer++;

        m_Buffer->vertex = (ts * glm::vec4(position.x, position.y + size.y, position.z, 1)).xyz();
        m_Buffer->color  = color;
        m_Buffer++;

        m_Buffer->vertex = (ts * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1)).xyz();
        m_Buffer->color  = color;
        m_Buffer++;

        m_Buffer->vertex = (ts * glm::vec4(position.x + size.x, position.y, position.z, 1)).xyz();
        m_Buffer->color  = color;
        m_Buffer++;

        m_IndexCount += 6;
    }

    void BatchRenderer2D::end(){
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void BatchRenderer2D::flush(){
        glBindVertexArray(m_VAO);
        m_IBO->bind();
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, 0);
        m_IBO->unbind();
        glBindVertexArray(0);
        m_IndexCount = 0;
    }
}
