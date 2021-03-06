#pragma once

#include <Renderer2D.hpp>
#include <Renderable2D.hpp>
#include <freetype-gl.h>
#include <cstddef>

namespace Pix{

#define RENDERER_MAX_SPRITES   50000
#define RENDERER_VERTEX_SIZE   sizeof(VertexData)
#define RENDERER_SPRITE_SIZE   RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE   RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE  RENDERER_MAX_SPRITES * 6

    class BatchRenderer2D : public Renderer2D{
        private:
            GLuint m_VBO, m_VAO;
            IndexBuffer *m_IBO;
            VertexData *m_Buffer;
            GLuint m_IndexCount;
            std::vector<GLuint> m_TextureSlots;

            ftgl::texture_atlas_t *m_FTAtlas;
            ftgl::texture_font_t  *m_FTFont;
        public:
            BatchRenderer2D();
            ~BatchRenderer2D();

            void begin() override;
            void end() override;
            void init();
            void submit(const Renderable2D* renderable) override;
            void drawString(const std::string &text, glm::vec3 position, glm::vec4 color) override;
            void flush() override;
    };
}
