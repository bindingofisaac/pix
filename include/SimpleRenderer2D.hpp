#pragma once

#include <Renderable2D.hpp>
#include <Renderer2D.hpp>
#include <deque>

namespace Pix{
    class SimpleRenderer2D : public Renderer2D{
        private:
            std::deque<const Renderable2D*> m_RenderQueue;
        public:
            void submit(const Renderable2D *renderable) override;
            void flush() override;
    };
}
