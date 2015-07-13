#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

            void setUniformMat4(const std::string&, const glm::mat4&);
            void enable();
            void disable();
    };
}
