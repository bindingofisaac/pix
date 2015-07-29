#include <Window.hpp>
#include <Layer2D.hpp>
#include <Group.hpp>
#include <Shader.hpp>
#include <Sprite.hpp>
#include <Texture.hpp>

using namespace Pix;

int main(){
    Window window("RPG UI", 960, 540);
    window.setClearColor(1, 1, 1, 1);

    Shader *genShader = new Shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    GLint texids[32];
    for(int i(0); i<32;i++) texids[i] = i;
    genShader->enable();
    genShader->setUniform1iv("textures", texids, 32);
    genShader->disable();

    Layer2D uilayer(genShader);
    Group *uigroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,0.0)));

    //uigroup->add(new Sprite(0 , 0    , 16 , 9 , new Texture("data/rpgui/background.png")));
    uigroup->add(new Sprite(0   , 0    , 4  , 2 , new Texture("data/rpgui/player.png")));
    uigroup->add(new Sprite(14  , 0.1f , 2  , 2 , new Texture("data/rpgui/map.png")));
    uigroup->add(new Sprite(4   , 1    , 8  , 3 , new Texture("data/rpgui/logo.png")));

    uigroup->add(new Sprite(4, 4, 4, 2, new Texture("data/rpgui/continue.png")));
    uigroup->add(new Sprite(8, 4, 4, 2, new Texture("data/rpgui/newgame.png")));

    uigroup->add(new Sprite(4, 6, 8, 1, new Texture("data/rpgui/exp.png")));

    uigroup->add(new Sprite(1, 7, 2, 2, new Texture("data/rpgui/health.png")));
    uigroup->add(new Sprite(4, 7, 2, 2, new Texture("data/rpgui/mana.png")));

    uigroup->add(new Sprite(7, 7, 5, 2, new Texture("data/rpgui/dialogue.png")));
    uigroup->add(new Sprite(14, 7, 2, 2, new Texture("data/rpgui/treasure.png")));


    uilayer.add(uigroup);

    while(window.running){
        window.clear();
        uilayer.render();
        window.update();
    }
    return 0;
}
