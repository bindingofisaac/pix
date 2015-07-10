#include <Window.hpp>
#include <Shader.hpp>
#include <Logger.hpp>
#include <VertexBuffer.hpp>
#include <IndexBuffer.hpp>

int main(){
    Pix::Window window("test game", 1080, 720);
    window.setClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    Pix::Shader shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    shader.enable();

    float vertices[] = {
        -0.5f, +0.5f,
        +0.5f, +0.5f,
        +0.5f, -0.5f,
        -0.5f, -0.5f
    };

    GLushort indices[] = { 0, 1, 2, 2, 3, 0 };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Pix::VertexBuffer vbo(vertices, 8, 2);
    Pix::IndexBuffer  ibo(indices, 6);
    vbo.bind();
    ibo.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    while(window.running){
        window.clear();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        window.update();
    }
    return 0;
}
