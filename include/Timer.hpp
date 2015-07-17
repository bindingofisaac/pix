#pragma once

#include<SDL/SDL.h>
#include<cstdlib>

namespace Pix{
    class Timer{
        private:
            long long m_Start;
            long long m_Timer;
            unsigned int m_Frames = 0;
        public:
            Timer(){
                m_Timer = 0;
                m_Start = SDL_GetTicks();
            }

            void reset(){
                m_Start = SDL_GetTicks();
            }

            long long elapsed(){
                long long current = SDL_GetTicks();
                return current - m_Start;
            }

            void logFPS(){
                m_Frames++;
                if(elapsed() - m_Timer > 1000) {
                    m_Timer += 1000;
                    logger<<m_Frames<<" FPS\n";
                    m_Frames = 0;
                }
            }
    };
}
