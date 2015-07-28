#include <Layer.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pix{
    Layer::Layer(Renderer2D *renderer, Shader *shader, glm::mat4 projectionMatrix) : m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix){
        m_Shader->enable();
        m_Shader->setUniformMat4("projection", m_ProjectionMatrix);
        m_Shader->disable();
    }
    
    Layer::~Layer(){
        for(int i=0;i<m_Renderables.size();i++) delete m_Renderables[i];
    }

    void Layer::add(Renderable2D* renderable){
        m_Renderables.push_back(renderable);
    }

    void Layer::render(){
        m_Renderer->begin();
        for(const Renderable2D* renderable : m_Renderables){
            renderable->submit(m_Renderer);
        }
        m_Renderer->drawString("Hello", glm::vec3(0, 0, 0), glm::vec4(0,1,1,1));
        m_Renderer->end();

        m_Shader->enable();
        m_Renderer->flush();
        m_Shader->disable();
    }
}
