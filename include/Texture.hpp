#pragma once

#include <string>
#include <GL/glew.h>
#include <ImageLoad.hpp>

namespace Pix{
    class Texture{
        private:
            std::string m_Path;
            GLuint m_TID;
            GLsizei m_Width, m_Height;

            GLuint load();
        public:
            Texture(const std::string& path);
            ~Texture();
            void bind() const;
            void unbind() const;

            inline unsigned int getWidth() { return m_Width; }
            inline unsigned int getHeight() { return m_Height; }
    };
}
