#pragma once

#include <Renderable2D.hpp>

namespace Pix{
    class Renderer2D{
        protected:
            virtual void submit(const Renderable2D *renderable) = 0;
            virtual void flush() = 0;
    };
}
