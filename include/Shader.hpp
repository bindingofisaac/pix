#pragma once

#include <GL/glew.h>
#include <Utils.hpp>

namespace Pix{
    class Shader{
        private:
            GLuint m_ShaderProgram;
            const std::string m_VertPath, m_FragPath;

            GLuint f_Load();
            GLint  f_GetUniformLocation(const std::string&);
        public:
            Shader(const std::string&, const std::string&);
            ~Shader();

            void enable();
            void disable();
    };
}
