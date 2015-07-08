#include <Window.hpp>
#include <Logger.hpp>

int main(){
    Pix::Window window("test game", 1080, 720);
    window.setClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    while(window.running){
        window.clear();
        window.update();
    }
    return 0;
}
