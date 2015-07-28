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
    Pix::Window window("test game", 960, 540);
    Pix::Timer timer;

    Pix::Shader *shader0 = new Pix::Shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    Pix::Layer2D layer0(shader0);
    Pix::Group *group0 = new Pix::Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0f))*glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)));
    Pix::Group *group1 = new Pix::Group(glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.0f))*glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 4.5f, 1)));

    GLint texids[32];
    for(int i=0;i<32;i++) texids[i] = i;

    Pix::Texture *texture0 = new Pix::Texture("test0.png");
    Pix::Texture *texture1 = new Pix::Texture("test1.jpg");
    Pix::Texture *texture2 = new Pix::Texture("test2.jpg");

    std::vector<Pix::Texture*> tex;
    tex.push_back(texture0);
    tex.push_back(texture1);
    tex.push_back(texture2);

    shader0->enable();

    shader0->setUniformMat4("projection", glm::ortho(0.0f, 16.0f, 9.0f, 0.0f));
    shader0->setUniform1iv("textures", texids, 32);
    shader0->disable();

    for(float i=0;i<16;i+=1.0f){
        for(float j=0;j<9;j+=1.0f){
            group0->add(new Pix::Sprite(i, j, 0.9f, 0.9f, glm::vec4(rand() % 1000 / 1000.0f,rand() % 1000 / 1000.0f,rand() % 1000 / 1000.0f,1)));
        }
    }

    group1->add(new Pix::Sprite(0.0f, 0.0f, 16.0f, 9.0f, tex[2]));

    layer0.add(group0);
    layer0.add(group1);

    window.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    SDL_ShowCursor(SDL_DISABLE);
    int x, y;
    while(window.running){
        window.clear();
           window.getMousePosition(x, y);
           shader0->enable();
           shader0->setUniform2f("light_pos", glm::vec2((float)(16*(x / 960.0f)), (float)(y *  9.0f / 540.0f))); 
           shader0->disable();
           layer0.render();
        window.update();
        timer.logFPS();
    }
    return 0;
}
