#pragma once

#include <GL/glew.h>
#include <Buffers.hpp>
#include <glm/glm.hpp>

namespace Pix{
    struct VertexData{
        glm::vec3 vertex;
        glm::vec4 color;
    };

    class Renderable2D{
        protected:
            glm::vec3 m_Position;
            glm::vec2 m_Size;
            glm::vec4 m_Color;

            VertexArray  *m_VertexArray;
            IndexBuffer  *m_IndexBuffer;
        public:
            Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color) : m_Position(position), m_Size(size), m_Color(color) {
                m_VertexArray = new VertexArray();
                GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
                m_IndexBuffer = new IndexBuffer(indices, 6);

                GLfloat vertices[] = {
                    position.x          , position.y          , position.z ,
                    position.x          , position.y + size.y , position.z ,
                    position.x + size.x , position.y + size.y , position.z ,
                    position.x + size.x , position.y          , position.z
                };

                GLfloat col[] = {
                    color.r, color.g, color.b, color.a,
                    color.r, color.g, color.b, color.a,
                    color.r, color.g, color.b, color.a,
                    color.r, color.g, color.b, color.a
                };

                m_VertexArray->add(new VertexBuffer(vertices, 4*3, 3), 0);
                m_VertexArray->add(new VertexBuffer(col, 4*4, 4), 1);

            }

            ~Renderable2D(){
                delete m_VertexArray;
                delete m_IndexBuffer;
            }

            inline const VertexArray* getVAO() const { return m_VertexArray; }
            inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

            inline const glm::vec3& getPosition() const { return m_Position; }
            inline const glm::vec4& getColor() const { return m_Color; }
            inline const glm::vec2& getSize() const { return m_Size; }
    };
}
