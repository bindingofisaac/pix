#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include<string>

namespace Pix{
    class Window{
        private:
            SDL_Window    *m_Window;
            SDL_GLContext m_Context;
            SDL_Event m_WindowEvent;
            int m_Width, m_Height;
            const std::string m_Title;
            
            void f_Create();
        public:
            Window(const std::string title, int width, int height);
            ~Window();

            void setClearColor(float, float, float, float);
            void clear();
            void update();
            bool running;
    };
}
