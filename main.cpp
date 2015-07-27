#include <Logger.hpp>
#include <Window.hpp>
#include <Timer.hpp>
#include <Shader.hpp>
#include <Sprite.hpp>
#include <BatchRenderer2D.hpp>
#include <Layer2D.hpp>
#include <Group.hpp>
#include <Texture.hpp>

int main(){
    Pix::Timer timer;
    Pix::Window window("test game", 960, 540);

    Pix::Shader *shader0 = new Pix::Shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    Pix::Layer2D layer0(shader0);
    Pix::Group *group0 = new Pix::Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0f))*glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)));

    shader0->enable();
    shader0->setUniformMat4("projection", glm::ortho(-1.0f, 17.0f, 10.0f, -1.0f));
    shader0->disable();

    for(float i=0;i<16;i+=1.0f){
        for(float j=0;j<9;j+=1.0f){
            group0->add(new Pix::Sprite(i, j, 0.9f, 0.9f, glm::vec4(1,1,1,1)));
        }
    }

    layer0.add(group0);

    
    glActiveTexture(GL_TEXTURE0);
    Pix::Texture texture("test.png");
    texture.bind();

    window.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    while(window.running){
        window.clear();
           layer0.render();
        window.update();
        timer.logFPS();
    }
    return 0;
}
