#pragma once

#include<Renderable2D.hpp>

namespace Pix{
    class Group : public Renderable2D{
        protected:
            std::vector<Renderable2D*> m_Renderables;
            glm::mat4 m_TransformationMatrix;
        public:
            Group(const glm::mat4 &transform);
            void add(Renderable2D* renderable);
            void submit(Renderer2D* renderer) const override;
    };
}
