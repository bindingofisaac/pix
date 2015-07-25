#pragma once

#include <Layer.hpp>
#include <BatchRenderer2D.hpp>

namespace Pix{
    class Layer2D : public Layer{
        public:
            Layer2D(Shader *shader);
            ~Layer2D();
    };
}
