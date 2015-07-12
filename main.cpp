#include <Window.hpp>
#include <Shader.hpp>
#include <Logger.hpp>
#include <SimpleRenderer2D.hpp>

int main(){
    Pix::Window window("test game", 1080, 720);
    Pix::Shader shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    Pix::Renderable2D *sprite1 = new Pix::Renderable2D(glm::vec3(0    , 0    , 0), glm::vec2(0.5, 0.5), glm::vec4(1, 0, 0, 1));
    Pix::Renderable2D *sprite2 = new Pix::Renderable2D(glm::vec3(-0.2f, -0.5f, 0), glm::vec2(0.2, 0.5), glm::vec4(1, 1, 1, 1));
    Pix::SimpleRenderer2D renderer;

    window.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    shader.enable();
    while(window.running){
        window.clear();
        renderer.submit(sprite1);
        renderer.submit(sprite2);
        renderer.flush();
        window.update();
    }
    return 0;
}
