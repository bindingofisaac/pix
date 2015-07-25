#pragma once

#define GLM_SWIZZLE
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

        public:
            Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color) : m_Position(position), m_Size(size), m_Color(color) {
            }

            ~Renderable2D(){
            }

            inline const glm::vec3& getPosition() const { return m_Position; }
            inline const glm::vec4& getColor() const { return m_Color; }
            inline const glm::vec2& getSize() const { return m_Size; }
    };
}
