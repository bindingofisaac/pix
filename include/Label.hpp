#pragma once

#include<Renderable2D.hpp>

namespace Pix{
    class Label : public Renderable2D{
        private:
            std::string m_Text;
        public:
            Label(std::string text, float x, float y, glm::vec4 color);
            virtual void submit(Renderer2D *renderer) const override;
            void setText(std::string text);
            ~Label();
    };
}
