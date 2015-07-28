#pragma once

#define GLM_SWIZZLE
#include <GL/glew.h>
#include <Buffers.hpp>
#include <glm/glm.hpp>

namespace Pix{
    class  Renderable2D;
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

            virtual void drawString(const std::string &text, glm::vec3 position, glm::vec4 color) = 0;

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
