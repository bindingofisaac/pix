#pragma once

#include <iostream>

namespace Pix{
    struct Logger{
        template<typename ANY> Logger& operator << (ANY &&x){
            std::cout<<x;
            return *this;
        }
    };

    extern Logger logger;
}
