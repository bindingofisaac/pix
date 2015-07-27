#pragma once

#include <Renderer2D.hpp>
#include <Renderable2D.hpp>
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
        public:
            BatchRenderer2D();
            ~BatchRenderer2D();

            void begin();
            void end();
            void init();
            void submit(const Renderable2D* renderable) override;
            void flush() override;
    };
}
