#include <Window.hpp>

namespace Pix{
    void Window::f_Create(){
        SDL_Init(SDL_INIT_EVERYTHING);
        // TODO: Check for errors

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, SDL_WINDOW_OPENGL);
        // TODO: check for errors

        m_Context = SDL_GL_CreateContext(m_Window);
        // TODO: check for errors

        glewExperimental = GL_TRUE;
        glewInit();
        // TODO: check for errors
        //
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Window::Window(const std::string title, int width, int height) : m_Window(nullptr), m_Title(title), m_Width(width), m_Height(height), running(true){
        f_Create();
    }

    Window::~Window(){
        // TODO: handle exceptions. what if there is now context? also destroy window
        SDL_GL_DeleteContext(m_Context);
        SDL_Quit();
    }

    void Window::setClearColor(float r, float g, float b, float a){
        glClearColor(r, g, b, a);
    }

    void Window::clear(){
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::update(){
        SDL_PollEvent(&m_WindowEvent);
        if(m_WindowEvent.type == SDL_QUIT){
            running = false;
        }
        if(m_WindowEvent.type == SDL_MOUSEMOTION){
            SDL_GetMouseState(&m_Xpos, &m_Ypos);
        }
        // Should be removed only for debugging 
        SDL_GL_SetSwapInterval(0);
        SDL_GL_SwapWindow(m_Window);
    }

    void Window::getMousePosition(int &x, int &y){
        x = m_Xpos;
        y = m_Ypos;
    }
}
