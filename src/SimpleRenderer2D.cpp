#include <SimpleRenderer2D.hpp>

namespace Pix{
    void SimpleRenderer2D::submit(const Renderable2D *renderable){
        m_RenderQueue.push_back(renderable);
    }

    void SimpleRenderer2D::flush(){
/*  
        //TODO implement static sprite
        while(!m_RenderQueue.empty()){
            const Renderable2D *renderable = m_RenderQueue.front();
            renderable->getVAO()->bind();
            renderable->getIBO()->bind();

            glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

            renderable->getIBO()->unbind();
            renderable->getVAO()->unbind();

            m_RenderQueue.pop_front();
            }
            */
    }
}
 
