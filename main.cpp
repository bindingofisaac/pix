#include <Window.hpp>
#include <Shader.hpp>
#include <Logger.hpp>
#include <Sprite.hpp>
#include <BatchRenderer2D.hpp>
#include <vector>

#include <cstdlib>

int main(){
    Pix::Window window("test game", 960, 540);
    Pix::Shader shader("data/shaders/simple.vert", "data/shaders/simple.frag");

    std::vector<Pix::Renderable2D*> sprites;
    Pix::BatchRenderer2D batch;

    glm::mat4 projection = glm::ortho(0.0f, 16.0f, 9.0f, 0.0f);

    std::srand(time(NULL));
    for(float y = 0; y < 9.0f; y+=1){
        for(float x = 0; x < 16.0f; x+=1){
            sprites.push_back(new Pix::Sprite(x, y, 0.9f, 0.9f, glm::vec4(rand() % 1000 / 1000.0f,0,1,1)));
        }
    }

    window.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    shader.enable();
    while(window.running){
        window.clear();
        shader.setUniformMat4("projection", projection);
        batch.begin();
            for(int i=0;i<sprites.size();i++){
                batch.submit(sprites[i]);
            }
            batch.flush();
        batch.end();
        window.update();
    }
    return 0;
}
