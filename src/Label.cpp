#include<Label.hpp>

namespace Pix{
    Label::Label(std::string text, float x, float y, glm::vec4 color) : Renderable2D(), m_Text(text){
        m_Position = glm::vec3(x, y, 0.0f);
        m_Color = color;
    }

    void Label::submit(Renderer2D *renderer) const{
        renderer->drawString(m_Text, m_Position, m_Color);
    }

    void Label::setText(std::string text){
        m_Text = text;
    }

    Label::~Label(){
    }
}
