#pragma once

#include <Renderable2D.hpp>

namespace Pix{
    class Renderer2D{
        public:
            virtual void begin() = 0;
            virtual void end() = 0;
            virtual void submit(const Renderable2D *renderable) = 0;
            virtual void flush() = 0;
    };
}
