#pragma once

#include <OpenGL.hpp>
#include<string>

namespace Pix{
    class Window{
        private:
            SDL_Window    *m_Window;
            SDL_GLContext m_Context;
            SDL_Event m_WindowEvent;
            const std::string m_Title;
            int m_Width, m_Height;
            int m_Xpos, m_Ypos;
            
            void f_Create();
        public:
            Window(const std::string title, int width, int height);
            ~Window();

            void getMousePosition(int &x,int &y);
            void setClearColor(float, float, float, float);
            void clear();
            void update();
            bool running;

            inline float getWidth(){ return m_Width; }
            inline float getHeight(){ return m_Height; }
    };
}
