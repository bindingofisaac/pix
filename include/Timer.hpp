#pragma once

#include<SDL/SDL.h>
#include<cstdlib>
#include<Logger.hpp>
#include<Label.hpp>

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

            void logFPS(Label *fps){
                m_Frames++;
                if(elapsed() - m_Timer > 1000) {
                    m_Timer += 1000;
                    fps->setText(std::to_string(m_Frames)+" FPS");
                    m_Frames = 0;
                }
            }
    };
}
