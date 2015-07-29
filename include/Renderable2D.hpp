#pragma once

#define GLM_SWIZZLE
#include <GL/glew.h>
#include <Buffers.hpp>
#include <glm/glm.hpp>

#include <vector>
#include <Renderer2D.hpp>
#include <Texture.hpp>

namespace Pix{
    struct VertexData{
        glm::vec3 vertex;
        glm::vec2 uv;
        float tid;
        glm::vec4 color;
    };

    class Renderable2D{
        private:
            void setDefaultUV(){
                m_UV.push_back(glm::vec2(0, 0));
                m_UV.push_back(glm::vec2(0, 1));
                m_UV.push_back(glm::vec2(1, 1));
                m_UV.push_back(glm::vec2(1, 0));
            }
        protected:
            glm::vec3 m_Position;
            glm::vec2 m_Size;
            glm::vec4 m_Color;
            Texture *m_Texture;
            std::vector <glm::vec2> m_UV;
            Renderable2D() : m_Color(glm::vec4(1)){ setDefaultUV(); m_Texture = nullptr; }
        public:
            Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)  : m_Position(position), m_Size(size), m_Color(color) { setDefaultUV(); m_Texture= nullptr; }
            Renderable2D(glm::vec3 position, glm::vec2 size, Texture *texture) : m_Position(position), m_Size(size), m_Texture(texture), m_Color(glm::vec4(1)){ setDefaultUV(); }

            virtual ~Renderable2D(){
            }

            virtual void submit(Renderer2D *renderer) const{
                renderer->submit(this);
            }

            inline const glm::vec3& getPosition() const { return m_Position; }
            inline const glm::vec4& getColor() const { return m_Color; }
            inline const glm::vec2& getSize() const { return m_Size; }
            inline const std::vector<glm::vec2>& getUV() const { return m_UV; }
            inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
    };
}
