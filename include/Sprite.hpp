#pragma once

#include <Renderable2D.hpp>

namespace Pix{
    class Sprite : public Renderable2D{
        public:
            Sprite(float x, float y, float width, float height, glm::vec4 color);
    };
}
