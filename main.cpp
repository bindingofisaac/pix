#include <Window.hpp>
#include <Shader.hpp>
#include <Logger.hpp>
#include <Sprite.hpp>
#include <BatchRenderer2D.hpp>
#include <vector>
#include <cstdlib>
#include <Timer.hpp>
#include <Layer2D.hpp>

int main(){
    Pix::Window window("test game", 960, 540);

    Pix::Shader *shader0 = new Pix::Shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    Pix::Shader *shader1 = new Pix::Shader("data/shaders/simple.vert", "data/shaders/simple.frag");

    Pix::Layer2D layer0(shader0);
    Pix::Layer2D layer1(shader1);

    std::vector<Pix::Renderable2D*> sprites;

    std::srand(time(NULL));
    for(float y = 0; y < 9.0f; y+=0.1f){
        for(float x = 0; x < 16.0f; x+=0.1f){
            sprites.push_back(new Pix::Sprite(x, y, 0.09f, 0.09f, glm::vec4(rand() % 1000 / 1000.0f,0,1,1)));
        }
    }

    for(int i=0;i<sprites.size();i++){
        layer0.add(sprites[i]);
    }

    layer1.add(new Pix::Sprite(0.0f, 0.0f, 4.0f, 4.0f, glm::vec4(1, 1, 1, 1)));
 

    window.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    Pix::Timer timer;
    while(window.running){
        window.clear();
           layer0.render();
           layer1.render();
        window.update();
        timer.logFPS();
    }
    return 0;
}
