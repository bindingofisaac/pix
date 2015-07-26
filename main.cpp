#include <Window.hpp>
#include <Shader.hpp>
#include <Logger.hpp>
#include <Sprite.hpp>
#include <BatchRenderer2D.hpp>
#include <Timer.hpp>
#include <Layer2D.hpp>
#include <Group.hpp>

int main(){
    Pix::Timer timer;
    Pix::Window window("test game", 960, 540);

    Pix::Shader *shader0 = new Pix::Shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    Pix::Layer2D layer0(shader0);
    Pix::Group *group0 = new Pix::Group(glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 3.0, 0.0f))*glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)));

    group0->add(new Pix::Sprite(0, 0, 6, 3, glm::vec4(1,1,1,1)));
    group0->add(new Pix::Sprite(0.5f, 0.5f, 5.0f, 2.0f, glm::vec4(1,0,0,1)));

    layer0.add(group0);

    window.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    while(window.running){
        window.clear();
           layer0.render();
        window.update();
        timer.logFPS();
    }
    return 0;
}
