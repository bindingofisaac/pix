#pragma once

#include <Renderable2D.hpp>

namespace Pix{
    class Renderer2D{
        protected:
            std::vector<glm::mat4> m_TransformationStack;
            Renderer2D(){
                m_TransformationStack.push_back(glm::mat4(1.0f));
            }
        public:
            virtual void begin() = 0;
            virtual void end() = 0;
            virtual void submit(const Renderable2D *renderable) = 0;
            virtual void flush() = 0;

            void push(glm::mat4 matrix, bool overide = false){
                if(overide){
                    m_TransformationStack.push_back(matrix);
                }else{
                    m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
                }
            }

            void pop(){
                if(m_TransformationStack.size() > 1){
                    m_TransformationStack.pop_back();
                }
            }
    };
}
