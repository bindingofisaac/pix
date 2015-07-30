#pragma once


#include <OpenGL.hpp>
#include <ImageLoad.hpp>
#include <string>

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
            inline unsigned int getID() { return m_TID; }
    };
}
