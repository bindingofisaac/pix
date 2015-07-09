#include <Window.hpp>
#include <Shader.hpp>
#include <Logger.hpp>

int main(){
    Pix::Window window("test game", 1080, 720);
    window.setClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    Pix::Shader shader("data/shaders/simple.vert", "data/shaders/simple.frag");

    float vertices[] = {
        +0.0f, +0.5f,
        +0.5f, -0.5f,
        -0.5f, -0.5f
    };

    GLuint vao, vbo;
    glGenBuffers(1, &vbo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    shader.enable();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    while(window.running){
        window.clear();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.update();
    }
    return 0;
}
