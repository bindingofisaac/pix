#include <Window.hpp>
#include <Shader.hpp>
#include <Logger.hpp>
#include <Buffers.hpp>

int main(){
    Pix::Window window("test game", 1080, 720);
    Pix::Shader shader("data/shaders/simple.vert", "data/shaders/simple.frag");
    shader.enable();

    float vertices[] = {
        -0.5f, +0.5f,
        +0.5f, +0.5f,
        +0.5f, -0.5f,
        -0.5f, -0.5f
    };

    float color[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    GLushort indices[] = { 0, 1, 2, 2, 3, 0 };

    Pix::VertexArray  vao;
    Pix::VertexBuffer *vbo = new Pix::VertexBuffer(vertices, 8, 2);
    Pix::VertexBuffer *col = new Pix::VertexBuffer(color, 12, 3);
    Pix::IndexBuffer  ibo(indices, 6);

    vao.add(vbo, 0);
    vao.add(col, 1);

    vao.bind();
    ibo.bind();
    window.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    while(window.running){
        window.clear();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        window.update();
    }
    return 0;
}
