#include<Layer2D.hpp>

namespace Pix{
    Layer2D::Layer2D(Shader *shader) : Layer(new BatchRenderer2D(), shader, glm::ortho(0.0f, 16.0f, 9.0f, 0.0f)){
    }

    Layer2D::~Layer2D(){
    }
}
